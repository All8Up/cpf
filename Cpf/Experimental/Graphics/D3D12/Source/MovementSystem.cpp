//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"

#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "Threading/ScopedLock.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;
using namespace EntityService;

bool MoverSystem::MoverComponent::Install()
{
	return ComponentFactoryInstall(iMoverComponent::kIID, &MoverSystem::MoverComponent::Create);
}

bool MoverSystem::MoverComponent::Remove()
{
	return ComponentFactoryRemove(iMoverComponent::kIID);
}

iComponent* MoverSystem::MoverComponent::Create(MultiCore::iSystem* system)
{
	return static_cast<iComponent*>(new MoverComponent(system));
}

COM::Result MoverSystem::MoverComponent::QueryInterface(COM::InterfaceID id, void** outPtr)
{
	if (id.GetID() == iMoverComponent::kIID.GetID())
	{
		iMoverComponent* mover = static_cast<iMoverComponent*>(this);
		mover->AddRef();
		*outPtr = mover;
		return COM::kOK;
	}

	*outPtr = nullptr;
	return COM::kUnknownInterface;
}



MoverSystem::MoverSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const Desc* desc)
	: mpApp(nullptr)
	, mpInstances(nullptr)
	, mpTime(nullptr)
	, mClockID(desc->mTimerID)
	, mInstanceID(desc->mInstanceID)
	, mEnableMovement(true)
	, mUseEBus(false)
{
	System::Initialize(rgy, owner, name);

	mpApp = static_cast<const Desc*>(desc)->mpApplication;

	// Build the stages.
	rgy->Create(nullptr, kEntityStageCID, iEntityStage::kIID, mpThreadStage.AsVoidPP());
	mpThreadStage->Initialize(this, kUpdate.GetString());

	rgy->Create(nullptr, kEntityStageCID, iEntityStage::kIID, mpEBusStage.AsVoidPP());
	mpEBusStage->Initialize(this, kUpdateEBus.GetString());

	// Add the stages to this system.
	AddStage(mpThreadStage);
	AddStage(mpEBusStage);

	// Disable the EBus comparison stage to start with.
	mpEBusStage->SetEnabled(false);
}

InstanceSystem* MoverSystem::GetInstanceSystem() const
{
	return mpInstances;
}

COM::Result MoverSystem::Configure()
{
	if (COM::Succeeded(GetOwner()->GetSystem(mClockID, &reinterpret_cast<MultiCore::iSystem*>(mpTime))) &&
		COM::Succeeded(GetOwner()->GetSystem(mInstanceID, &reinterpret_cast<MultiCore::iSystem*>(mpInstances))))
		return COM::kOK;
	return COM::kInvalid;
}

bool MoverSystem::Install()
{
	return System::Install(kID, &MoverSystem::_Creator);
}
bool MoverSystem::Remove()
{
	return System::Remove(kID);
}

void MoverSystem::EnableMovement(bool flag)
{
	mEnableMovement = flag;

	mpThreadStage->SetEnabled(flag && !mUseEBus);
	mpEBusStage->SetEnabled(flag && mUseEBus);

	mpApp->ReconfigurePipeline();
}

void MoverSystem::UseEBus(bool flag)
{
	mUseEBus = flag;
	EnableMovement(mEnableMovement);
}

MultiCore::iSystem* MoverSystem::_Creator(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
{
	return new MoverSystem(rgy, owner, name, static_cast<const Desc*>(desc));
}


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent(MultiCore::iSystem* owner)
	: mpMover(static_cast<MoverSystem*>(owner))
{}

//////////////////////////////////////////////////////////////////////////
ComponentID MoverSystem::MoverComponent::GetID() const
{
	return kID;
}

void MoverSystem::MoverComponent::Activate()
{
	mpMover->mpThreadStage->AddUpdate(mpMover, GetEntity(), &MoverComponent::_Threaded);
	mpMover->mpEBusStage->AddUpdate(mpMover, GetEntity(), &MoverComponent::_EBus);
}

void MoverSystem::MoverComponent::Deactivate()
{
	mpMover->mpThreadStage->RemoveUpdate(mpMover, GetEntity(), &MoverComponent::_Threaded);
	mpMover->mpEBusStage->RemoveUpdate(mpMover, GetEntity(), &MoverComponent::_EBus);
}

void MoverSystem::MoverComponent::_Threaded(iSystem* system, iEntity* object)
{
	MoverSystem* mover = static_cast<MoverSystem*>(system);
	MultiCore::iTimer* timer = mover->mpTime;

	int i = int(object->GetID().GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
	float magnitude = Magnitude(pos + Vector3fv(0.0f, 50.0f, 0.0f)) * 0.03f;
	magnitude *= magnitude;
	float time = float(Time::Seconds(timer->GetTime()));
	float angle = sinf(0.25f * time);
	pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
	pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
	pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time) *
		Matrix33fv::AxisAngle(Vector3fv(1.0f, 0.0f, 0.0f), time*2.0f);

	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	CPF_ASSERT(instances != nullptr);

	instances[i].mScale = Vector3f(1.0f);
	instances[i].mOrientation0 = Vector3f(orientation[0].xyz);
	instances[i].mOrientation1 = Vector3f(orientation[1].xyz);
	instances[i].mOrientation2 = Vector3f(orientation[2].xyz);
	instances[i].mTranslation = Vector3f(pos.xyz);
}

void MoverSystem::MoverComponent::_EBus(iSystem* system, iEntity* object)
{
	MoverSystem* mover = static_cast<MoverSystem*>(system);
	Threading::ScopedLock<Threading::Mutex> lock(mover->mMutex);

	MultiCore::iTimer* timer = mover->mpTime;

	int i = int(object->GetID().GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
	float magnitude = Magnitude(pos + Vector3fv(0.0f, 50.0f, 0.0f)) * 0.03f;
	magnitude *= magnitude;
	float time = float(Time::Seconds(timer->GetTime()));
	float angle = sinf(0.25f * time);
	pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
	pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
	pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time) *
		Matrix33fv::AxisAngle(Vector3fv(1.0f, 0.0f, 0.0f), time*2.0f);
	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	instances[i].mScale = Vector3f(1.0f);
	instances[i].mOrientation0 = Vector3f(orientation[0].xyz);
	instances[i].mOrientation1 = Vector3f(orientation[1].xyz);
	instances[i].mOrientation2 = Vector3f(orientation[2].xyz);
	instances[i].mTranslation = Vector3f(pos.xyz);
}

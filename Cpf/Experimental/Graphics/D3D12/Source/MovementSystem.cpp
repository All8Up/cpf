//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"
#include "Graphics/iImageView.hpp"

#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "Threading/ScopedLock.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;
using namespace EntityService;
using namespace MultiCore;

COM::Result MoverSystem::MoverComponent::Install(Plugin::iRegistry* regy)
{
	class ClassInstance : public tRefCounted<Plugin::iClassInstance>
	{
	public:
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
		COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
		{
			if (outIface)
			{
				*outIface = new MoverSystem::MoverComponent();
				return *outIface ? COM::kOK : COM::kOutOfMemory;
			}
			return COM::kInvalidParameter;
		}
	};
	return regy->Install(kMoverComponentCID, new ClassInstance());
}

COM::Result MoverSystem::MoverComponent::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverComponentCID);
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



MoverSystem::MoverSystem()
	: mpApp(nullptr)
	, mpInstances(nullptr)
	, mpTime(nullptr)
	, mEnableMovement(true)
	, mUseEBus(false)
{
}

InstanceSystem* MoverSystem::GetInstanceSystem() const
{
	return mpInstances;
}

COM::Result MoverSystem::Configure(MultiCore::iPipeline* pipeline)
{
	if (COM::Succeeded(pipeline->GetSystem(mClockID, &reinterpret_cast<MultiCore::iSystem*>(mpTime))) &&
		COM::Succeeded(pipeline->GetSystem(mInstanceID, &reinterpret_cast<MultiCore::iSystem*>(mpInstances))))
		return COM::kOK;
	return COM::kInvalid;
}

COM::Result MoverSystem::Install(Plugin::iRegistry* regy)
{
	class ClassInstance : public tRefCounted<Plugin::iClassInstance>
	{
	public:
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
		COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
		{
			if (outIface)
			{
				*outIface = new MoverSystem();
				return *outIface ? COM::kOK : COM::kOutOfMemory;
			}
			return COM::kInvalidParameter;
		}
	};
	return regy->Install(kMoverSystemCID, new ClassInstance());
}
COM::Result MoverSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverSystemCID);
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


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent()
	: mpMover(nullptr)
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

float gTime = 0.0f;
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
	(void)transform;

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
	(void)transform;

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time) *
		Matrix33fv::AxisAngle(Vector3fv(1.0f, 0.0f, 0.0f), time*2.0f);
	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	instances[i].mScale = Vector3f(1.0f);
	instances[i].mOrientation0 = Vector3f(orientation[0].xyz);
	instances[i].mOrientation1 = Vector3f(orientation[1].xyz);
	instances[i].mOrientation2 = Vector3f(orientation[2].xyz);
	instances[i].mTranslation = Vector3f(pos.xyz);
}


//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL MoverSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case MoverSystem::kIID.GetID():
			*outIface = static_cast<MoverSystem*>(this);
			break;
		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL MoverSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* gdesc)
{
	(void)rgy;
	if (name)
	{
		const Desc* desc = static_cast<const Desc*>(gdesc);
		mpApp = nullptr;
		mpInstances = nullptr;
		mpTime = nullptr;
		mClockID = desc->mTimerID;
		mInstanceID = desc->mInstanceID;
		mEnableMovement = true;
		mUseEBus = false;

		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(nullptr, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (COM::Succeeded(result))
		{
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
			return COM::kOK;
		}
		return result;
	}
	return COM::kInvalidParameter;
}

SystemID CPF_STDCALL MoverSystem::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL MoverSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL MoverSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

COM::Result CPF_STDCALL MoverSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL MoverSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL MoverSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL MoverSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL MoverSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

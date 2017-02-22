//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/Pipeline.hpp"
#include "GO/Object.hpp"
#include "GO/Component.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"
#include "GO/Components/TransformComponent.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;

MoverSystem::MoverSystem(const String& name, const Desc* desc)
	: System(name)
	, mpApp(nullptr)
	, mpInstances(nullptr)
	, mpTime(nullptr)
	, mClockID(desc->mTimerID)
	, mInstanceID(desc->mInstanceID)
{
	mpMoverStage = MultiCore::Stage::Create<GO::ObjectStage>(this, "Mover");
	mpMoverStage->SetDependencies({ { mInstanceID, InstanceSystem::kBeginID } });
	AddStage(mpMoverStage);
}

InstanceSystem* MoverSystem::GetInstanceSystem() const
{
	return mpInstances;
}

bool MoverSystem::Configure()
{
	mpTime = static_cast<GO::Timer*>(GetOwner()->GetSystem(mClockID));
	mpInstances = static_cast<InstanceSystem*>(GetOwner()->GetSystem(mInstanceID));

	return mpTime && mpInstances;
}

bool MoverSystem::Install()
{
	return System::Install(kID, &MoverSystem::_Creator);
}
bool MoverSystem::Remove()
{
	return System::Remove(kID);
}

void MoverSystem::EnableMovement(bool flag) const
{
	mpMoverStage->SetEnabled(flag);
}

MultiCore::System* MoverSystem::_Creator(const String& name, const System::Desc* desc)
{
	return new MoverSystem(name, static_cast<const Desc*>(desc));
}


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent(MoverSystem* mover)
	: mpMover(mover)
{}

	//////////////////////////////////////////////////////////////////////////
GO::ComponentID MoverSystem::MoverComponent::GetID() const
{
	return kID;
}

void MoverSystem::MoverComponent::Activate()
{
	mpMover->mpMoverStage->AddUpdate(mpMover, GetObject(), &MoverComponent::_Update);
}

void MoverSystem::MoverComponent::Deactivate()
{
	mpMover->mpMoverStage->RemoveUpdate(mpMover, GetObject(), &MoverComponent::_Update);
}

void MoverSystem::MoverComponent::_Update(System* system, GO::Object* object)
{
	MoverSystem* mover = static_cast<MoverSystem*>(system);
	const GO::Timer* timer = mover->mpTime;

	int i = int(object->GetID().GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
	float magnitude = Magnitude(pos + Vector3f(0.0f, 50.0f, 0.0f)) * 0.03f;
	magnitude *= magnitude;
	float time = float(Time::Seconds(timer->GetTime()));
	float angle = sinf(0.25f * time);
	pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
	pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
	pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;
	object->GetComponent<GO::TransformComponent>()->GetTransform().SetTranslation(pos);

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time);

	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
	instances[i].mOrientation0 = orientation[0].xyz;
	instances[i].mOrientation1 = orientation[1].xyz;
	instances[i].mOrientation2 = orientation[2].xyz;
	instances[i].mTranslation = Vector3f(pos.xyz);
}

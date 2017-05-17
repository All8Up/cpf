//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"
#include "Graphics/iImageView.hpp"
#include "Math/Trigonometric.hpp"

#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "Threading/ScopedLock.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;
using namespace EntityService;
using namespace MultiCore;

GOM::Result MoverSystem::MoverComponent::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kMoverComponentCID, new Plugin::tClassInstance<MoverSystem::MoverComponent>());
}

GOM::Result MoverSystem::MoverComponent::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverComponentCID);
}

GOM::Result MoverSystem::MoverComponent::QueryInterface(GOM::InterfaceID id, void** outPtr)
{
	if (id.GetID() == iMoverComponent::kIID.GetID())
	{
		iMoverComponent* mover = static_cast<iMoverComponent*>(this);
		mover->AddRef();
		*outPtr = mover;
		return GOM::kOK;
	}

	*outPtr = nullptr;
	return GOM::kUnknownInterface;
}



MoverSystem::MoverSystem(GOM::iUnknown*)
	: mpApp(nullptr)
	, mpInstances(nullptr)
	, mpTime(nullptr)
	, mEnableMovement(true)
{
}

InstanceSystem* MoverSystem::GetInstanceSystem() const
{
	return mpInstances;
}

GOM::Result MoverSystem::Configure(MultiCore::iPipeline* pipeline)
{
	if (GOM::Succeeded(pipeline->GetSystem(mClockID, &reinterpret_cast<MultiCore::iSystem*>(mpTime))) &&
		GOM::Succeeded(pipeline->GetSystem(mInstanceID, &reinterpret_cast<MultiCore::iSystem*>(mpInstances))))
		return GOM::kOK;
	return GOM::kInvalid;
}

GOM::Result MoverSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kMoverSystemCID, new Plugin::tClassInstance<MoverSystem>());
}
GOM::Result MoverSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverSystemCID);
}

void MoverSystem::EnableMovement(bool flag)
{
	mEnableMovement = flag;

	mpThreadStage->SetEnabled(flag);
	mpApp->ReconfigurePipeline();
}


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent(GOM::iUnknown*)
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
}

void MoverSystem::MoverComponent::Deactivate()
{
	mpMover->mpThreadStage->RemoveUpdate(mpMover, GetEntity(), &MoverComponent::_Threaded);
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
	float angle = Sin(0.25f * time);
	pos.x = Sin(angle * magnitude) * pos.x - Cos(angle * magnitude) * pos.z;
	pos.y = (Sin(angle) + 0.5f) * pos.y * magnitude;
	pos.z = Cos(angle * magnitude) * pos.x + Sin(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();
	transform->GetTransform().SetTranslation(pos);

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time) *
		Matrix33fv::AxisAngle(Vector3fv(1.0f, 0.0f, 0.0f), time*2.0f);

	// TODO: Move into drawable component.
	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	CPF_ASSERT(instances != nullptr);

	instances[i].mScale = Vector3f(1.0f);
	instances[i].mOrientation0 = Vector3f(orientation[0].xyz);
	instances[i].mOrientation1 = Vector3f(orientation[1].xyz);
	instances[i].mOrientation2 = Vector3f(orientation[2].xyz);
	instances[i].mTranslation = Vector3f(pos.xyz);
}


//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL MoverSystem::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case MoverSystem::kIID.GetID():
			*outIface = static_cast<MoverSystem*>(this);
			break;
		default:
			return GOM::kNotImplemented;
		}

		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL MoverSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* gdesc)
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

		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(this, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
		{
			mpApp = static_cast<const Desc*>(desc)->mpApplication;

			// Build the stages.
			rgy->Create(nullptr, kEntityStageCID, iEntityStage::kIID, mpThreadStage.AsVoidPP());
			mpThreadStage->Initialize(this, kUpdate.GetString());

			// Add the stages to this system.
			AddStage(mpThreadStage);
			return GOM::kOK;
		}
		return result;
	}
	return GOM::kInvalidParameter;
}

SystemID CPF_STDCALL MoverSystem::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL MoverSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

GOM::Result CPF_STDCALL MoverSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

GOM::Result CPF_STDCALL MoverSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

GOM::Result CPF_STDCALL MoverSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

GOM::Result CPF_STDCALL MoverSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL MoverSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

GOM::Result CPF_STDCALL MoverSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

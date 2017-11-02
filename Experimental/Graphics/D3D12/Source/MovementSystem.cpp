//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"
#include "CPF/Graphics/iImageView.hpp"
#include "Math/Trigonometric.hpp"

#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "Threading/ScopedLock.hpp"

using namespace CPF;
using namespace Math;
using namespace EntityService;
using namespace MultiCore;

GOM::Result MoverSystem::MoverComponent::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kMoverComponentCID.GetID(), new Plugin::tClassInstance<MoverComponent>());
}

GOM::Result MoverSystem::MoverComponent::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverComponentCID.GetID());
}

GOM::Result MoverSystem::MoverComponent::QueryInterface(uint64_t id, void** outPtr)
{
	if (id == kIID.GetID())
	{
		iMoverComponent* mover = static_cast<iMoverComponent*>(this);
		mover->AddRef();
		*outPtr = mover;
		return GOM::kOK;
	}

	*outPtr = nullptr;
	return GOM::kUnknownInterface;
}



MoverSystem::MoverSystem(Plugin::iRegistry*, iUnknown*)
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

GOM::Result MoverSystem::Configure(iExecutionPlan* pipeline)
{
	if (GOM::Succeeded(pipeline->GetSystem(mClockID, &reinterpret_cast<iSystem*>(mpTime))) &&
		GOM::Succeeded(pipeline->GetSystem(mInstanceID, &reinterpret_cast<iSystem*>(mpInstances))))
		return GOM::kOK;
	return GOM::kInvalid;
}

GOM::Result MoverSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kMoverSystemCID.GetID(), new Plugin::tClassInstance<MoverSystem>());
}
GOM::Result MoverSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kMoverSystemCID.GetID());
}

void MoverSystem::EnableMovement(bool flag)
{
	mEnableMovement = flag;

	mpThreadStage->SetEnabled(flag);
	mpApp->ReconfigurePipeline();
}


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent(Plugin::iRegistry*, iUnknown*)
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
	using Real = typename Math::Transform::Real;
	using Quat = typename Math::Transform::Quat;
	using Vector3 = typename Math::Transform::Vector3;
	using Matrix44 = typename Math::Transform::Matrix44;
	using Matrix33 = Math::Matrix33<typename Vector3::Type>;

	MoverSystem* mover = static_cast<MoverSystem*>(system);
	iTimer* timer = mover->mpTime;

	int i = int(object->GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3 pos((xc - count / 2) * Real(1.5), (yc - count / 2) * Real(1.5), (zc - count / 2) * Real(1.5));
	Real magnitude = Magnitude(pos + Vector3(Real(0.0), Real(50.0), Real(0.0))) * Real(0.03);
	magnitude *= magnitude;
	Real time = Real(Time::Seconds(timer->GetTime()));
	Real angle = Sin(Real(0.25) * time);
	pos.x = Sin(angle * magnitude) * pos.x - Cos(angle * magnitude) * pos.z;
	pos.y = (Sin(angle) + Real(0.5)) * pos.y * magnitude;
	pos.z = Cos(angle * magnitude) * pos.x + Sin(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();
	transform->GetTransform().SetTranslation(pos);

	static const Vector3 YAxis = Vector3(0.0, 1.0, 0.0);
	Matrix33 orientation = Matrix33::Identity(); // Matrix33::AxisAngle(YAxis, time) /* *
		// Matrix33::AxisAngle(Vector3(1.0, 0.0, 0.0), time*2.0f) */;

	// TODO: Move into drawable component.
	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	CPF_ASSERT(instances != nullptr);

	instances[i].mScale = Vector3f(1.0);
	instances[i].mOrientation0 = Vector3f(orientation[0].xyz);
	instances[i].mOrientation1 = Vector3f(orientation[1].xyz);
	instances[i].mOrientation2 = Vector3f(orientation[2].xyz);
	instances[i].mTranslation = Vector3f(pos.xyz);
}


//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL MoverSystem::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case kIID.GetID():
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
		auto result = rgy->Create(this, kStageListCID.GetID(), iStageList::kIID.GetID(), mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
		{
			mpApp = static_cast<const Desc*>(desc)->mpApplication;

			// Build the stages.
			rgy->Create(nullptr, kEntityStageCID.GetID(), iEntityStage::kIID.GetID(), mpThreadStage.AsVoidPP());
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

GOM::Result CPF_STDCALL MoverSystem::GetDependencies(iExecutionPlan* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

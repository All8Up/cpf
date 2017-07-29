//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iSystem.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Helpers/ComponentBase.hpp"
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "Hash/HashString.hpp"
#include "InstanceSystem.hpp"

namespace Cpf
{
	class ExperimentalD3D12;
	class MoverSystem;

	class iMoverComponent : public EntityService::iComponent
	{
	public:
	};

	static constexpr GOM::ClassID kMoverSystemCID = GOM::ClassID("MoverSystemClass"_crc64);
	static constexpr GOM::ClassID kMoverComponentCID = GOM::ClassID("MoverSystem::MoverComponent"_crc64);

	class MoverSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iMoverSystem"_crc64);

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Mover System"_hashString);
		static constexpr MultiCore::StageID kUpdate = Hash::Create<MultiCore::StageID_tag>("Update"_hashString);

		struct Desc : iSystem::Desc
		{
			ExperimentalD3D12* mpApplication;
			MultiCore::SystemID mTimerID;
			MultiCore::SystemID mInstanceID;
		};

		static GOM::Result Install(Plugin::iRegistry*);
		static GOM::Result Remove(Plugin::iRegistry*);

		// Component(s) supplied.
		class MoverComponent;

		MoverSystem(GOM::iUnknown*);
		InstanceSystem* GetInstanceSystem() const;
		GOM::Result CPF_STDCALL Configure(MultiCore::iExecutionPlan*) override;
		void EnableMovement(bool flag);

		// iBase
		GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		// iSystem
		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		// GOM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return GOM::kOK; }

		// iStageList
		GOM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		GOM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		GOM::Result CPF_STDCALL GetDependencies(MultiCore::iExecutionPlan* owner, int32_t*, MultiCore::BlockDependency*) override;

		GOM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		GOM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

	private:
		ExperimentalD3D12* mpApp;

		// system interdependencies.
		InstanceSystem* mpInstances;
		MultiCore::iTimer* mpTime;	// The clock this mover is attached to.
		IntrusivePtr<EntityService::iEntityStage> mpThreadStage;
		MultiCore::SystemID mClockID;
		MultiCore::SystemID mInstanceID;

		//
		bool mEnableMovement;
		Threading::Mutex mMutex;

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};


	class MoverSystem::MoverComponent : public EntityService::ComponentBase<iMoverComponent>
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		static constexpr EntityService::ComponentID kID = EntityService::ComponentID("Mover Component"_crc64);

		//
		static GOM::Result Install(Plugin::iRegistry*);
		static GOM::Result Remove(Plugin::iRegistry*);
		static iComponent* Create(iSystem*);

		//
		void SetSystem(MultiCore::iSystem* system) override { mpMover = static_cast<MoverSystem*>(system); }
		MultiCore::iSystem* GetSystem() override { return mpMover; }

		//////////////////////////////////////////////////////////////////////////
		MoverComponent(GOM::iUnknown*);

		GOM::Result QueryInterface(uint64_t id, void**) override;

		//////////////////////////////////////////////////////////////////////////
		EntityService::ComponentID GetID() const;

		void Activate() override;
		void Deactivate() override;

	private:
		static void _Threaded(iSystem* system, EntityService::iEntity* object);
		static void _EBus(iSystem* system, EntityService::iEntity* object);

		MoverSystem* mpMover;
	};
}

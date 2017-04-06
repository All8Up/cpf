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

	static constexpr COM::ClassID kMoverSystemCID = COM::ClassID("MoverSystemClass"_crc64);
	static constexpr COM::ClassID kMoverComponentCID = COM::ClassID("MoverSystem::MoverComponent"_crc64);

	class MoverSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("iMoverSystem"_crc64);

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Mover System"_hashString);
		static constexpr MultiCore::StageID kUpdate = Hash::Create<MultiCore::StageID_tag>("Update"_hashString);
		static constexpr MultiCore::StageID kUpdateEBus = Hash::Create<MultiCore::StageID_tag>("Update EBus"_hashString);

		struct Desc : iSystem::Desc
		{
			ExperimentalD3D12* mpApplication;
			MultiCore::SystemID mTimerID;
			MultiCore::SystemID mInstanceID;
		};

		static COM::Result Install(Plugin::iRegistry*);
		static COM::Result Remove(Plugin::iRegistry*);

		// Component(s) supplied.
		class MoverComponent;

		MoverSystem();
		InstanceSystem* GetInstanceSystem() const;
		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override;
		void EnableMovement(bool flag);
		void UseEBus(bool flag);

		// iUnknown
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

		// iSystem
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		// COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return COM::kOK; }

		// iStageList
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		COM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

	private:
		ExperimentalD3D12* mpApp;

		// system interdependencies.
		InstanceSystem* mpInstances;
		MultiCore::iTimer* mpTime;	// The clock this mover is attached to.
		IntrusivePtr<EntityService::iEntityStage> mpThreadStage;
		IntrusivePtr<EntityService::iEntityStage> mpEBusStage;
		MultiCore::SystemID mClockID;
		MultiCore::SystemID mInstanceID;

		//
		bool mEnableMovement;
		bool mUseEBus;
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
		static COM::Result Install(Plugin::iRegistry*);
		static COM::Result Remove(Plugin::iRegistry*);
		static iComponent* Create(iSystem*);

		//
		void SetOwner(MultiCore::iSystem* system) override { mpMover = static_cast<MoverSystem*>(system); }
		MultiCore::iSystem* GetOwner() override { return mpMover; }

		//////////////////////////////////////////////////////////////////////////
		MoverComponent();

		COM::Result QueryInterface(COM::InterfaceID id, void**) override;

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

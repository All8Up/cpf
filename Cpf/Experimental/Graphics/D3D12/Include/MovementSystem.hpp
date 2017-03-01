//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "EntityService/Interfaces/Systems/iTimerSystem.hpp"
#include "EntityService/Interfaces/iComponent.hpp"
#include "EntityService/Helpers/ComponentBase.hpp"
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "Hash/HashString.hpp"
#include "InstanceSystem.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	class iMoverComponent : public EntityService::iComponent
	{
	public:
	};

	class MoverSystem : public MultiCore::System
	{
	public:
		static constexpr auto kID = "Mover System"_hashString;
		static constexpr auto kUpdate = "Update"_hashString;
		static constexpr auto kUpdateEBus = "Update EBus"_hashString;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mTimerID;
			MultiCore::SystemID mInstanceID;
		};

		// Component(s) supplied.
		class MoverComponent;

		MoverSystem(MultiCore::Pipeline* owner, const char* name, const EntityService::SystemDependencies& deps, const Desc* desc);
		InstanceSystem* GetInstanceSystem() const;
		bool Configure() override;
		static bool Install();
		static bool Remove();
		void EnableMovement(bool flag);
		void UseEBus(bool flag);

	private:
		static System* _Creator(MultiCore::Pipeline* owner, const char* name, const System::Desc* desc, const EntityService::SystemDependencies& deps);

		ExperimentalD3D12* mpApp;

		// system interdependencies.
		InstanceSystem* mpInstances;
		const EntityService::Timer* mpTime;	// The clock this mover is attached to.
		EntityService::EntityStage* mpThreadStage;
		EntityService::EntityStage* mpEBusStage;
		MultiCore::SystemID mClockID;
		MultiCore::SystemID mInstanceID;

		//
		bool mEnableMovement;
		bool mUseEBus;
		Platform::Threading::Mutex mMutex;
	};


	class MoverSystem::MoverComponent
		: public EntityService::ComponentBase<iMoverComponent>
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		static constexpr EntityService::ComponentID kID = EntityService::ComponentID("Mover Component"_crc64);

		//
		static bool Install();
		static bool Remove();
		static iComponent* Create(System*);

		//////////////////////////////////////////////////////////////////////////
		MoverComponent(System* owner);

		bool QueryInterface(InterfaceID id, void**) override;

		//////////////////////////////////////////////////////////////////////////
		EntityService::ComponentID GetID() const;

		void Activate() override;
		void Deactivate() override;

	private:
		static void _Threaded(System* system, EntityService::iEntity* object);
		static void _EBus(System* system, EntityService::iEntity* object);

		MoverSystem* mpMover;
	};
}

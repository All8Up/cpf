//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/System.hpp"
#include "GO/Systems/Timer.hpp"
#include "GO/Component.hpp"
#include "Hash/HashString.hpp"
#include "InstanceSystem.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	class MoverSystem : public MultiCore::System
	{
	public:
		static constexpr auto kID = MultiCore::SystemID("Mover System"_crc64);
		static constexpr auto kMoverStage = "Mover Stage"_stringHash;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mTimerID;
			MultiCore::SystemID mInstanceID;
		};

		// Component(s) supplied.
		class MoverComponent;

		MoverSystem(const String& name, const Desc* desc);
		InstanceSystem* GetInstanceSystem() const;
		bool Configure() override;
		static bool Install();
		static bool Remove();
		void EnableMovement(bool flag) const;

	private:
		static System* _Creator(const String& name, const System::Desc* desc, const Dependencies& deps);

		ExperimentalD3D12* mpApp;

		// system interdependencies.
		InstanceSystem* mpInstances;
		const GO::Timer* mpTime;	// The clock this mover is attached to.
		GO::ObjectStage* mpMoverStage;
		MultiCore::SystemID mClockID;
		MultiCore::SystemID mInstanceID;
	};


	class MoverSystem::MoverComponent : public GO::Component
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		static constexpr GO::ComponentID kID = GO::ComponentID("Mover Component"_crc64);

		//////////////////////////////////////////////////////////////////////////
		MoverComponent(MoverSystem* mover);

		//////////////////////////////////////////////////////////////////////////
		GO::ComponentID GetID() const;

		void Activate() override;
		void Deactivate() override;

	private:
		static void _Update(System* system, GO::Object* object);

		MoverSystem* mpMover;
	};
}

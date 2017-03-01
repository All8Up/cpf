//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "Instance.hpp"
#include "MultiCore/System.hpp"
#include "MultiCore/Stage.hpp"
#include "Hash/HashString.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	class InstanceSystem : public MultiCore::System
	{
	public:
		using StageID = EntityService::StageID;

		static constexpr auto kID = "Instance Manager"_hashString;

		static constexpr auto kBegin = "Instance Begin"_hashString;
		static constexpr auto kEnd = "Instance End"_hashString;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(MultiCore::Pipeline* owner, const char* name, const EntityService::SystemDependencies& deps, const Desc* desc);

		Instance* GetInstances() const { return mpInstances; }

		static bool Install()
		{
			return System::Install(kID, &InstanceSystem::_Creator);
		}
		static bool Remove()
		{
			return System::Remove(kID);
		}

	private:
		static System* _Creator(MultiCore::Pipeline* owner, const char* name, const System::Desc* desc, const EntityService::SystemDependencies& deps)
		{
			return new InstanceSystem(owner, name, deps, static_cast<const Desc*>(desc));
		}

		static void _Begin(Concurrency::ThreadContext&, void* context);
		static void _End(Concurrency::ThreadContext&, void* context);

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}

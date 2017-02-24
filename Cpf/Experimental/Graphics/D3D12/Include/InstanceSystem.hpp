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

		static constexpr auto kID = MultiCore::SystemID("Instance Manager"_crc64);

		static constexpr Hash::StringHash kBegin = "Instance Begin"_stringHash;
		static constexpr Hash::StringHash kEnd = "Instance End"_stringHash;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(const String& name, const EntityService::SystemDependencies& deps, const Desc* desc);

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
		static System* _Creator(const String& name, const System::Desc* desc, const EntityService::SystemDependencies& deps)
		{
			return new InstanceSystem(name, deps, static_cast<const Desc*>(desc));
		}

		static void _Begin(Concurrency::ThreadContext&, void* context);
		static void _End(Concurrency::ThreadContext&, void* context);

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}

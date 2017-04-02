//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "Instance.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Hash/HashString.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	class InstanceSystem : public MultiCore::System
	{
	public:
		using StageID = EntityService::StageID;

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Instance Manager"_hashString);

		static constexpr MultiCore::StageID kBegin = Hash::Create<MultiCore::StageID_tag>("Instance Begin"_hashString);
		static constexpr MultiCore::StageID kEnd = Hash::Create<MultiCore::StageID_tag>("Instance End"_hashString);

		struct Desc : System::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(MultiCore::iPipeline* owner, const char* name, const Desc* desc);

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
		static iSystem* _Creator(MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
		{
			return new InstanceSystem(owner, name, static_cast<const Desc*>(desc));
		}

		static void _Begin(Concurrency::ThreadContext&, void* context);
		static void _End(Concurrency::ThreadContext&, void* context);

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}

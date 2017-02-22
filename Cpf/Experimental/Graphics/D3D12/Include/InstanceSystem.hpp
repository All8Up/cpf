//////////////////////////////////////////////////////////////////////////
#pragma once
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
		static constexpr auto kID = MultiCore::SystemID("Instance Manager"_crc64);

		static constexpr Hash::StringHash kBegin = "Instance Begin"_stringHash;

		struct Desc : System::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(const String& name, const Desc* desc)
			: System(name)
			, mpApp(desc->mpApplication)
			, mRenderID(desc->mRenderSystemID)
			, mpInstances(nullptr)
		{
			{
				MultiCore::SingleUpdateStage* stage = MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, "Instance Begin");
				stage->SetUpdate(&InstanceSystem::_Begin, this);
				stage->SetDependencies({ { mRenderID, StageID("Begin Frame"_crc64) } });
				AddStage(stage);
			}
			/*
			MultiCore::SingleUpdateStage::Desc {
				{ GetID(), kBegin.ID }
			};
			*/
			{
				MultiCore::SingleUpdateStage* stage = MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, "Instance End");
				stage->SetUpdate(&InstanceSystem::_End, this);
				stage->SetDependencies({ { GetID(), MultiCore::StageID(kBegin.ID) } });
				AddStage(stage);
			}
		}

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
		static System* _Creator(const String& name, const System::Desc* desc, const Dependencies& deps)
		{
			return new InstanceSystem(name, static_cast<const Desc*>(desc));
		}

		static void _Begin(Concurrency::ThreadContext&, void* context);
		static void _End(Concurrency::ThreadContext&, void* context);

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}

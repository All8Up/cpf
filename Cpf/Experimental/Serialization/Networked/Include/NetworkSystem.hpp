//////////////////////////////////////////////////////////////////////////
#pragma once
#include "asio.hpp"
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	static constexpr GOM::ClassID kNetworkSystemCID = GOM::ClassID("NetworkSystemCID"_crc64);

	class NetworkSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("NetworkSystem"_crc64);

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Network System"_hashString);

		static GOM::Result Install(Plugin::iRegistry*);
		static GOM::Result Remove(Plugin::iRegistry*);

		struct Desc : public iSystem::Desc
		{};

		// iBase
		GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		// iSystem
		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		GOM::Result CPF_STDCALL Configure(MultiCore::iExecutionPlan*) override { return GOM::kOK; }

		// iStageList
		GOM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		GOM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		GOM::Result CPF_STDCALL GetDependencies(MultiCore::iExecutionPlan* owner, int32_t*, MultiCore::BlockDependency*) override;

		GOM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		GOM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

		NetworkSystem(GOM::iUnknown*);

	private:
		static void _Update(const Concurrency::WorkContext*, void*);

		asio::io_service mASIO;

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}

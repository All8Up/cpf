//////////////////////////////////////////////////////////////////////////
#pragma once
#include "asio.hpp"
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	static constexpr COM::ClassID kNetworkSystemCID = COM::ClassID("NetworkSystemCID"_crc64);

	class NetworkSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("NetworkSystem"_crc64);

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Network System"_hashString);

		static COM::Result Install(Plugin::iRegistry*);
		static COM::Result Remove(Plugin::iRegistry*);

		struct Desc : public iSystem::Desc
		{};

		// iUnknown
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

		// iSystem
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return COM::kOK; }

		// iStageList
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		COM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

		NetworkSystem(COM::iUnknown*);

	private:
		static void _Update(const Concurrency::WorkContext*, void*);

		asio::io_service mASIO;

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}

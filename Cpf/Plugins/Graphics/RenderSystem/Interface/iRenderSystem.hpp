//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iSystem.hpp"

namespace CPF
{
	static constexpr GOM::ClassID kRenderSystemCID = GOM::ClassID("Cpf::RenderSystemCID"_crc64);

	struct iRenderSystem : tRefCounted<MultiCore::iSystem>
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iRenderSystem"_crc64);

		// TODO: Make sure this is a good idea.
		static constexpr MultiCore::SystemID kSystemID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);
	};
}

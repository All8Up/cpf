//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	static constexpr COM::ClassID kRenderSystemCID = COM::ClassID("Cpf::RenderSystemCID"_crc64);

	struct iRenderSystem : tRefCounted<MultiCore::iSystem>
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iRenderSystem"_crc64);

		// TODO: Make sure this is a good idea.
		static constexpr MultiCore::SystemID kSystemID = Hash::Create<MultiCore::SystemID_tag>("Render System"_hashString);
	};
}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iRenderPass.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct RenderPassDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			static constexpr COM::ClassID kRenderPassCID = COM::ClassID("Adapter::D3D12::RenderPass"_crc64);

			class RenderPass : public tRefCounted<Graphics::iRenderPass>
			{
			public:
				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				COM::Result CPF_STDCALL Initialize(const Graphics::RenderPassDesc* desc);
			};
		}
	}
}

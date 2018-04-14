//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Platform/Graphics/iPipeline.hpp"
#include "D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct PipelineStateDesc;
		struct iPipeline;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Device;
			class ResourceBinding;


			class Pipeline final : public GOM::tUnknown<Graphics::iPipeline>
			{
			public:
				Pipeline(Device*, const Graphics::PipelineStateDesc*, const ResourceBinding* CPF_GFX_DEBUG_PARAM_DECL);
				virtual ~Pipeline();

				ID3D12PipelineState* GetPipelineState() const { return mpPipelineState; }

			private:
				IntrusivePtr<ID3D12PipelineState> mpPipelineState;
			};
		}
	}
}

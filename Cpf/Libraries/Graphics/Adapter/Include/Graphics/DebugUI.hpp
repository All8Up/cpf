//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Resources
	{
		class Locator;
	}

	namespace Graphics
	{
		class iImage;
		class iDevice;
		class iShader;
		class iSampler;
		class iPipeline;
		class iResourceBinding;

		class DebugUI : public tRefCounted<iRefCounted>
		{
		public:
			DebugUI();
			~DebugUI() override;

			bool Initialize(iDevice*, Resources::Locator*);

		private:
			iDevice* mpDevice;
			Resources::Locator* mpLocator;
			IntrusivePtr<iShader> mpVertexShader;
			IntrusivePtr<iShader> mpPixelShader;
			IntrusivePtr<iResourceBinding> mpResourceBinding;
			IntrusivePtr<iPipeline> mpPipeline;
			IntrusivePtr<iImage> mpUIAtlas;
			IntrusivePtr<iSampler> mpSampler;
		};
	}
}

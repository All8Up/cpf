//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		template <typename TYPE>
		TYPE Defaults();

		template <typename TYPE>
		struct BuilderType;

		template <typename TYPE>
		typename BuilderType<TYPE>::Builder Build()
		{
			return typename BuilderType<TYPE>::Builder();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#include "Graphics/Range.hpp"
#include "Graphics/iBlob.hpp"

#include "Graphics/iInstance.hpp"
#include "Graphics/iAdapter.hpp"
#include "Graphics/iDevice.hpp"
#include "Graphics/iSwapChain.hpp"
#include "Graphics/iCommandPool.hpp"
#include "Graphics/iCommandBuffer.hpp"
#include "Graphics/iFence.hpp"
#include "Graphics/iShader.hpp"
#include "Graphics/iPipeline.hpp"
#include "Graphics/iResourceBinding.hpp"
#include "Graphics/iResource.hpp"
#include "Graphics/iIndexBuffer.hpp"
#include "Graphics/iVertexBuffer.hpp"
#include "Graphics/iConstantBuffer.hpp"

#include "Graphics/ResourceDesc.hpp"
#include "Graphics/ResourceBindingDesc.hpp"

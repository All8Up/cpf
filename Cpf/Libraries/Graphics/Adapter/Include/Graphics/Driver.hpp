//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_DEBUG
#	define CPF_GFX_TRACKING
#endif
#ifdef CPF_GFX_TRACKING
#	define CPF_GFX_DEBUG_PARAM_DECL , const char* dbgFilename=nullptr, int dbgLineNumber=0
#	define CPF_GFX_DEBUG_PARAM_DEF , const char* dbgFilename, int dbgLineNumber
#	define CPF_GFX_DEBUG_PARAMS , __FILE__, __LINE__
#	define CPF_GFX_DEBUG_FORWARD , dbgFilename, dbgLineNumber
#else
#	define CPF_GFX_DEBUG_PARAM_DECL
#	define CPF_GFX_DEBUG_PARAM_DEF
#	define CPF_GFX_DEBUG_PARAMS
#	define CPF_GFX_DEBUG_FORWARD
#endif

//////////////////////////////////////////////////////////////////////////
#include "Graphics/Range.hpp"
#include "Graphics/BinaryBlob.hpp"
#include "Graphics/BufferUsage.hpp"

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

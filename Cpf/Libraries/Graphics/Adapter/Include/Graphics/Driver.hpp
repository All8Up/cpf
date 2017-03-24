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
#	define CPF_GFX_DEBUG_PARAMS
#	define CPF_GFX_DEBUG_FORWARD
#endif

//////////////////////////////////////////////////////////////////////////
#include "Graphics/Range.hpp"
#include "Graphics/BinaryBlob.hpp"
#include "Graphics/BufferUsage.hpp"

#include "Graphics/Interfaces/iInstance.hpp"
#include "Graphics/Interfaces/iAdapter.hpp"
#include "Graphics/Interfaces/iDevice.hpp"
#include "Graphics/Interfaces/iSwapChain.hpp"
#include "Graphics/Interfaces/iCommandPool.hpp"
#include "Graphics/Interfaces/iCommandBuffer.hpp"
#include "Graphics/Interfaces/iFence.hpp"
#include "Graphics/Interfaces/iShader.hpp"
#include "Graphics/Interfaces/iPipeline.hpp"
#include "Graphics/Interfaces/iResourceBinding.hpp"
#include "Graphics/Interfaces/iResource.hpp"
#include "Graphics/Interfaces/iIndexBuffer.hpp"
#include "Graphics/Interfaces/iVertexBuffer.hpp"
#include "Graphics/Interfaces/iConstantBuffer.hpp"

#include "Graphics/Descriptors/ResourceDesc.hpp"
#include "Graphics/Descriptors/ResourceBindingDesc.hpp"

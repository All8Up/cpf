//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_GRAPHICS_DRIVER
#		define CPF_EXPORT_GRAPHICS_DRIVER
#	else // CPF_STATIC_GRAPHICS_DRIVER
#		if CPF_BUILD_GRAPHICS_DRIVER
#			define CPF_EXPORT_GRAPHICS_DRIVER CPF_EXPORT
#		else
#			define CPF_EXPORT_GRAPHICS_DRIVER CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_GRAPHICS_DRIVER CPF_EXPORT
#	else
#		define CPF_EXPORT_GRAPHICS_DRIVER
#	endif
#endif // CPF_TARGET_WINDOWS

//////////////////////////////////////////////////////////////////////////
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

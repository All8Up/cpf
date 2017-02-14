//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


namespace Cpf
{
	namespace Graphics
	{
		enum class Format : int32_t
		{
			eNone,

			eR8,
			eR8u,
			eR8s,
			eR8un,
			eR8sn,
			eR16,
			eR16u,
			eR16s,
			eR16un,
			eR16sn,
			eR16f,
			eR32,
			eR32u,
			eR32s,
			eR32f,

			eRG8,
			eRG8u,
			eRG8s,
			eRG8un,
			eRG8sn,
			eRG16,
			eRG16u,
			eRG16s,
			eRG16un,
			eRG16sn,
			eRG16f,
			eRG32,
			eRG32u,
			eRG32s,
			eRG32f,

			eRGB32,
			eRGB32u,
			eRGB32s,
			eRGB32f,

			eRGBA8,
			eRGBA8u,
			eRGBA8s,
			eRGBA8un,
			eRGBA8sn,
			eRGBA8uns,

			eRGBA16,
			eRGBA16u,
			eRGBA16s,
			eRGBA16un,
			eRGBA16sn,
			eRGBA16f,

			eRGBA32,
			eRGBA32u,
			eRGBA32s,
			eRGBA32f,


			eD32f
		};

		size_t GetFormatSize(Format format);
	}
}

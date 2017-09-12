//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


namespace CPF
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


			eD32f,
			eR24G8,
			eD24unS8u
		};

		inline size_t GetFormatSize(Format format)
		{
			switch (format)
			{
			case Format::eNone:
				return size_t(-1);

			case Format::eR8:
			case Format::eR8u:
			case Format::eR8s:
			case Format::eR8un:
			case Format::eR8sn:
				return 1;

			case Format::eR16:
			case Format::eR16u:
			case Format::eR16s:
			case Format::eR16un:
			case Format::eR16sn:
			case Format::eR16f:
				return 2;

			case Format::eR32:
			case Format::eR32u:
			case Format::eR32s:
			case Format::eR32f:
				return 4;

			case Format::eRG8:
			case Format::eRG8u:
			case Format::eRG8s:
			case Format::eRG8un:
			case Format::eRG8sn:
				return 2;

			case Format::eRG16:
			case Format::eRG16u:
			case Format::eRG16s:
			case Format::eRG16un:
			case Format::eRG16sn:
			case Format::eRG16f:
				return 4;

			case Format::eRG32:
			case Format::eRG32u:
			case Format::eRG32s:
			case Format::eRG32f:
				return 8;

			case Format::eRGB32:
			case Format::eRGB32u:
			case Format::eRGB32s:
			case Format::eRGB32f:
				return 12;

			case Format::eRGBA8:
			case Format::eRGBA8u:
			case Format::eRGBA8s:
			case Format::eRGBA8un:
			case Format::eRGBA8sn:
			case Format::eRGBA8uns:
				return 4;

			case Format::eRGBA16:
			case Format::eRGBA16u:
			case Format::eRGBA16s:
			case Format::eRGBA16un:
			case Format::eRGBA16sn:
			case Format::eRGBA16f:
				return 8;

			case Format::eRGBA32:
			case Format::eRGBA32u:
			case Format::eRGBA32s:
			case Format::eRGBA32f:
				return 16;

			case Format::eD32f:
			case Format::eR24G8:
			case Format::eD24unS8u:
				return 4;
			}
			return size_t(-1);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Platform/Graphics/InputLayoutDesc.hpp"
#include "CPF/Platform/Graphics/InputElementDesc.hpp"
#include "CPF/Platform/Graphics/InputClassification.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct InputLayoutBuilder
		{
			operator const CPF::STD::Vector<InputElementDesc>& ()
			{
				return mElements;
			}

			InputLayoutBuilder& Element(const char* semantic, int32_t index, Format format, int32_t slot, int32_t offset, InputClassification classification, int32_t stepping)
			{
				mElements.push_back(InputElementDesc{semantic, index, format, slot, offset, classification, stepping});
				return *this;
			}

		private:
			CPF::STD::Vector<InputElementDesc> mElements;
		};

		template <>
		struct BuilderType<InputLayoutDesc>
		{
			using Builder = InputLayoutBuilder;
		};
	}
}

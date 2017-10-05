//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/InputLayoutDesc.hpp"
#include <initializer_list>

namespace CPF
{
	namespace Graphics
	{
		struct InputLayoutBuilder
		{
			operator const CPF::Vector<InputElementDesc>& ()
			{
				return mElements;
			}

			InputLayoutBuilder& Element(const char* semantic, int32_t index, Format format, int32_t slot, int32_t offset, InputClassification classification, int32_t stepping)
			{
				mElements.push_back(InputElementDesc{semantic, index, format, slot, offset, classification, stepping});
				return *this;
			}

		private:
			CPF::Vector<InputElementDesc> mElements;
		};

		template <>
		struct BuilderType<InputLayoutDesc>
		{
			using Builder = InputLayoutBuilder;
		};
	}
}

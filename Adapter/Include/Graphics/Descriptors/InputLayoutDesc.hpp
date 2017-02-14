//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Format.hpp"
#include <initializer_list>

namespace Cpf
{
	namespace Graphics
	{
		/* @brief: Classification */
		enum class InputClassification : int32_t
		{
			ePerVertex = 0,
			ePerInstance
		};

		/* @brief: Element description. */
		class ElementDesc
		{
		public:
			ElementDesc();
			ElementDesc(const char* semantic, Format format, InputClassification classification = InputClassification::ePerVertex, int32_t stepping = 0);

			const char* GetSemantic() const;
			int32_t GetIndex() const;
			Format GetFormat() const;
			ElementDesc& Slot(int32_t slot) { mSlot = slot; return *this; }
			int32_t GetSlot() const;
			int32_t GetOffset() const;
			InputClassification GetClassification() const;
			int32_t GetStepping() const;

		private:
			friend class InputLayoutDesc;

			const char* mpSemantic;
			int32_t mIndex;
			Format mFormat;
			int32_t mSlot;
			int32_t mOffset;
			InputClassification mClass;
			int32_t mInstanceStepping;
		};

		class InputLayoutDesc
		{
		public:
			InputLayoutDesc();
			InputLayoutDesc(const InputLayoutDesc& rhs) noexcept;
			InputLayoutDesc(std::initializer_list<ElementDesc>);
			~InputLayoutDesc();

			InputLayoutDesc& operator =(const InputLayoutDesc& rhs);

			size_t GetCount() const;
			const ElementDesc* GetElementDescs() const;

		private:
			int32_t mCount;
			ElementDesc* mpElements;
		};
	}
}

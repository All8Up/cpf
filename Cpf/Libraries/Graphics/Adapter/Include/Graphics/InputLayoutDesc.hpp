//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/FormatSize.hpp"
#include "Graphics/InputClassification.hpp"
#include "Graphics/ElementDesc.hpp"
#include "UnorderedMap.hpp"
#include "String.hpp"
#include <initializer_list>

namespace CPF
{
	namespace Graphics
	{
		class cElementDesc : public ElementDesc
		{
		public:
			cElementDesc();
			cElementDesc(const char* semantic, Format format, InputClassification classification = InputClassification::ePerVertex, int32_t stepping = 0);

			const char* GetSemantic() const;
			int32_t GetIndex() const;
			Format GetFormat() const;
			ElementDesc& Slot(int32_t slot) { mSlot = slot; return *this; }
			int32_t GetSlot() const;
			int32_t GetOffset() const;
			InputClassification GetClassification() const;
			int32_t GetStepping() const;

		private:
			friend class cInputLayoutDesc;
		};

		struct InputLayoutDesc
		{
			int32_t mCount;
			ElementDesc* mpElements;
		};

		class cInputLayoutDesc : public InputLayoutDesc
		{
		public:
			cInputLayoutDesc();
			cInputLayoutDesc(const cInputLayoutDesc& rhs) noexcept;
			cInputLayoutDesc(std::initializer_list<ElementDesc>);
			~cInputLayoutDesc();

			cInputLayoutDesc& operator =(const cInputLayoutDesc& rhs);

			size_t GetCount() const;
			const ElementDesc* GetElementDescs() const;
		};


		//////////////////////////////////////////////////////////////////////////

		inline
		cElementDesc::cElementDesc()
			: ElementDesc
		{
			nullptr,
			-1,
			Format::eNone,
			0,
			-1,
			InputClassification::ePerVertex,
			0
		}
		{
		}

		inline
		cElementDesc::cElementDesc(const char* semantic, Format format, InputClassification classification, int32_t stepping)
			: ElementDesc
		{
			semantic,
			-1,
			format,
			0,
			-1,
			classification,
			stepping
		}
		{
		}

		inline
		const char* cElementDesc::GetSemantic() const
		{
			return mpSemantic;
		}

		inline
		int32_t cElementDesc::GetIndex() const
		{
			return mIndex;
		}

		inline
		Format cElementDesc::GetFormat() const
		{
			return mFormat;
		}

		inline
		int32_t cElementDesc::GetSlot() const
		{
			return mSlot;
		}

		inline
		int32_t cElementDesc::GetOffset() const
		{
			return mOffset;
		}

		inline
		InputClassification cElementDesc::GetClassification() const
		{
			return mClass;
		}

		inline
		int32_t cElementDesc::GetStepping() const
		{
			return mInstanceStepping;
		}

		//////////////////////////////////////////////////////////////////////////
		inline
		cInputLayoutDesc::cInputLayoutDesc()
			: InputLayoutDesc{ 0, nullptr }
		{}

		inline
		cInputLayoutDesc::cInputLayoutDesc(const cInputLayoutDesc& rhs) noexcept
			: InputLayoutDesc{ rhs.mCount, new ElementDesc[rhs.mCount] }
		{
			for (int i = 0; i < mCount; ++i)
				mpElements[i] = rhs.mpElements[i];
		}

		inline
		cInputLayoutDesc::cInputLayoutDesc(std::initializer_list<ElementDesc> elements)
			: InputLayoutDesc{ int32_t(elements.size()), nullptr }
		{
			// TODO: Likely need to make copies of the semantic names.

			using SemanticMap = UnorderedMap<String, int>;
			SemanticMap semanticMap;

			int32_t lastSlot = 0;
			int32_t offset = 0;

			mpElements = new ElementDesc[mCount];
			if (mpElements)
			{
				int current = 0;
				for (const auto& element : elements)
				{
					auto& elementRef = mpElements[current++];

					if (element.mSlot != lastSlot)
					{
						// Reset tracking data between slots (i.e. streams).
						offset = 0;
						lastSlot = element.mSlot;
					}

					// Handle semantic name and index.
					if (semanticMap.find(element.mpSemantic) == semanticMap.end())
					{
						// Semantic not in map, this is index 0.
						semanticMap[element.mpSemantic] = 0;
						elementRef.mpSemantic = element.mpSemantic;
						elementRef.mIndex = 0;
					}
					else
					{
						int32_t index = semanticMap[element.mpSemantic] + 1;
						semanticMap[element.mpSemantic] = index;
						elementRef.mpSemantic = element.mpSemantic;
						elementRef.mIndex = index;
					}

					elementRef.mFormat = element.mFormat;
					elementRef.mSlot = element.mSlot;
					elementRef.mOffset = (element.mOffset == -1) ? offset : element.mOffset;
					// Define all offsets or no offsets, mixing and matching is not allowed.
					CPF_ASSERT(offset == -1 ? element.mOffset == -1 : true);
					elementRef.mClass = element.mClass;
					elementRef.mInstanceStepping = element.mInstanceStepping;

					// Handle offset tracking.
					if (offset != -1)
					{
						if (element.mOffset!= -1)
							offset = -1;
						else
							offset += int32_t(GetFormatSize(element.mFormat));
					}
				}
			}
		}

		inline
		cInputLayoutDesc::~cInputLayoutDesc()
		{
			if (mpElements)
				delete[] mpElements;
		}

		inline
		cInputLayoutDesc& cInputLayoutDesc::operator =(const cInputLayoutDesc& rhs)
		{
			if (mpElements)
				delete[] mpElements;
			mCount = rhs.mCount;
			mpElements = new ElementDesc[mCount];
			for (int i = 0; i < mCount; ++i)
				mpElements[i] = rhs.mpElements[i];
			return *this;
		}

		inline
		size_t cInputLayoutDesc::GetCount() const
		{
			return mCount;
		}

		inline
		const ElementDesc* cInputLayoutDesc::GetElementDescs() const
		{
			return mpElements;
		}
	}
}

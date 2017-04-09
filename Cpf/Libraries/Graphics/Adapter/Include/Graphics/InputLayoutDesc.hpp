//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Format.hpp"
#include "Graphics/InputClassification.hpp"
#include "UnorderedMap.hpp"
#include "String.hpp"
#include <initializer_list>

namespace Cpf
{
	namespace Graphics
	{
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


		//////////////////////////////////////////////////////////////////////////

		inline
		ElementDesc::ElementDesc()
			: mpSemantic(nullptr)
			, mIndex(-1)
			, mFormat(Format::eNone)
			, mSlot(0)
			, mOffset(-1)
			, mClass(InputClassification::ePerVertex)
			, mInstanceStepping(0)
		{
		}

		inline
		ElementDesc::ElementDesc(const char* semantic, Format format, InputClassification classification, int32_t stepping)
			: mpSemantic(semantic)
			, mIndex(-1) // Compute during build.
			, mFormat(format)
			, mSlot(0)
			, mOffset(-1) // Compute during build.
			, mClass(classification)
			, mInstanceStepping(stepping)
		{
		}

		inline
		const char* ElementDesc::GetSemantic() const
		{
			return mpSemantic;
		}

		inline
		int32_t ElementDesc::GetIndex() const
		{
			return mIndex;
		}

		inline
		Format ElementDesc::GetFormat() const
		{
			return mFormat;
		}

		inline
		int32_t ElementDesc::GetSlot() const
		{
			return mSlot;
		}

		inline
		int32_t ElementDesc::GetOffset() const
		{
			return mOffset;
		}

		inline
		InputClassification ElementDesc::GetClassification() const
		{
			return mClass;
		}

		inline
		int32_t ElementDesc::GetStepping() const
		{
			return mInstanceStepping;
		}

		//////////////////////////////////////////////////////////////////////////
		inline
		InputLayoutDesc::InputLayoutDesc()
			: mCount(0)
			, mpElements(nullptr)
		{}

		inline
		InputLayoutDesc::InputLayoutDesc(const InputLayoutDesc& rhs) noexcept
			: mCount(rhs.mCount)
			, mpElements(new ElementDesc[rhs.mCount])
		{
			for (int i = 0; i < mCount; ++i)
				mpElements[i] = rhs.mpElements[i];
		}

		inline
		InputLayoutDesc::InputLayoutDesc(std::initializer_list<ElementDesc> elements)
			: mCount(int32_t(elements.size()))
			, mpElements(nullptr)
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

					if (element.GetSlot() != lastSlot)
					{
						// Reset tracking data between slots (i.e. streams).
						offset = 0;
						lastSlot = element.GetSlot();
					}

					// Handle semantic name and index.
					if (semanticMap.find(element.GetSemantic()) == semanticMap.end())
					{
						// Semantic not in map, this is index 0.
						semanticMap[element.GetSemantic()] = 0;
						elementRef.mpSemantic = element.GetSemantic();
						elementRef.mIndex = 0;
					}
					else
					{
						int32_t index = semanticMap[element.GetSemantic()] + 1;
						semanticMap[element.GetSemantic()] = index;
						elementRef.mpSemantic = element.GetSemantic();
						elementRef.mIndex = index;
					}

					elementRef.mFormat = element.GetFormat();
					elementRef.mSlot = element.GetSlot();
					elementRef.mOffset = (element.GetOffset() == -1) ? offset : element.GetOffset();
					// Define all offsets or no offsets, mixing and matching is not allowed.
					CPF_ASSERT(offset == -1 ? element.GetOffset() == -1 : true);
					elementRef.mClass = element.GetClassification();
					elementRef.mInstanceStepping = element.GetStepping();

					// Handle offset tracking.
					if (offset != -1)
					{
						if (element.GetOffset() != -1)
							offset = -1;
						else
							offset += int32_t(GetFormatSize(element.GetFormat()));
					}
				}
			}
		}

		inline
		InputLayoutDesc::~InputLayoutDesc()
		{
			if (mpElements)
				delete[] mpElements;
		}

		inline
		InputLayoutDesc& InputLayoutDesc::operator =(const InputLayoutDesc& rhs)
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
		size_t InputLayoutDesc::GetCount() const
		{
			return mCount;
		}

		inline
		const ElementDesc* InputLayoutDesc::GetElementDescs() const
		{
			return mpElements;
		}
	}
}

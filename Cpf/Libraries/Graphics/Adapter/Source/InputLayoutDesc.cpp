//////////////////////////////////////////////////////////////////////////
#include "Graphics/InputLayoutDesc.hpp"
#include "UnorderedMap.hpp"
#include "String.hpp"

using namespace Cpf;
using namespace Graphics;

//////////////////////////////////////////////////////////////////////////
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

const char* ElementDesc::GetSemantic() const
{
	return mpSemantic;
}

int32_t ElementDesc::GetIndex() const
{
	return mIndex;
}

Format ElementDesc::GetFormat() const
{
	return mFormat;
}

int32_t ElementDesc::GetSlot() const
{
	return mSlot;
}

int32_t ElementDesc::GetOffset() const
{
	return mOffset;
}

InputClassification ElementDesc::GetClassification() const
{
	return mClass;
}

int32_t ElementDesc::GetStepping() const
{
	return mInstanceStepping;
}

//////////////////////////////////////////////////////////////////////////
InputLayoutDesc::InputLayoutDesc()
	: mCount(0)
	, mpElements(nullptr)
{}

InputLayoutDesc::InputLayoutDesc(const InputLayoutDesc& rhs) noexcept
	: mCount(rhs.mCount)
	, mpElements(new ElementDesc[rhs.mCount])
{
	for (int i = 0; i < mCount; ++i)
		mpElements[i] = rhs.mpElements[i];
}

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

			if (element.GetSlot()!=lastSlot)
			{
				// Reset tracking data between slots (i.e. streams).
				offset = 0;
				lastSlot = element.GetSlot();
			}

			// Handle semantic name and index.
			if (semanticMap.find(element.GetSemantic())==semanticMap.end())
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
			if (offset!=-1)
			{
				if (element.GetOffset() != -1)
					offset = -1;
				else
					offset += int32_t(GetFormatSize(element.GetFormat()));
			}
		}
	}
}

InputLayoutDesc::~InputLayoutDesc()
{
	if (mpElements)
		delete[] mpElements;
}

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

size_t InputLayoutDesc::GetCount() const
{
	return mCount;
}

const ElementDesc* InputLayoutDesc::GetElementDescs() const
{
	return mpElements;
}

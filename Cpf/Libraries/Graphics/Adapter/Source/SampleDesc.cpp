//////////////////////////////////////////////////////////////////////////
#include "Graphics/SampleDesc.hpp"

using namespace Cpf;
using namespace Graphics;

SampleDesc::SampleDesc()
	: mCount(1)
	, mQuality(0)
{}

SampleDesc::SampleDesc(int32_t count, int32_t quality)
	: mCount(count)
	, mQuality(quality)
{}

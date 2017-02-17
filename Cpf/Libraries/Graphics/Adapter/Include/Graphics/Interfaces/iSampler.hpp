//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"


namespace Cpf
{
	namespace Graphics
	{
		enum class FilterMode : uint32_t
		{
			ePoint = 0,
			eLinear = 1
		};
		enum class WrapMode : uint32_t
		{
			eWrap = 1,
			eMirror = 2,
			eClamp = 3,
			eBorder = 4,
			eMirrorOnce = 5
		};

		struct SamplerDesc
		{
			FilterMode mMinFilter;
			FilterMode mMagFilter;
			FilterMode mMipFilter;
			WrapMode mUWrap;
			WrapMode mVWrap;
			WrapMode mWWrap;
			float mLodMin;
			float mLodMax;
			float mLodBias;
		};

		class iSampler : public tRefCounted<iRefCounted>
		{
		public:
			virtual ~iSampler() = 0;
		};
	}
}

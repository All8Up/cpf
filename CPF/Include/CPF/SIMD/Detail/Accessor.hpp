//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace SIMD
	{
		template <typename TYPE>
		class Accessor
		{
		public:
			using StorageType = TYPE;
			using LaneType = typename TYPE::LaneType;

			template <int LANE>
			LaneType GetLane() const { return GetType()->GetLane<LANE>(); }

		protected:
			TYPE* GetType() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* GetType() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};
	}
}

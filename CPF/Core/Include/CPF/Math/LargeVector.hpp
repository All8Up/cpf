//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Math/Vector3v.hpp"
#include "CPF/Math/Vector4v.hpp"

namespace CPF
{
	namespace Math
	{
		// General information.
		static constexpr float kHalfSectorSize = 4096.0f;	// 4,096 meters
		static constexpr float kSectorSize = 2.0f * kHalfSectorSize;

		/**
		 * @class Proxy
		 * @brief A proxy is a simple, though ugly and potentially unsafe
		 * if used incorrectly, reference to the containing object.  The
		 * purpose of this is to implement properties much like C# which
		 * are accessed via simple member value (i.e. 'a.b' style) syntax
		 * yet will go through get/set like operations.  This is needed
		 * in cases where the property can not safely have it's address
		 * taken or it doesn't exist in the form being represented.
		 * In all current compilers this has been tested and will be
		 * optimized away such that there is no additional overhead to
		 * using the proxy.
		 * @tparam VALUETYPE The value type that is represented by the proxy.
		 */
		template <typename TYPE>
		class Proxy
		{
		public:
			using ValueType = TYPE;

		protected:
			TYPE* Get()
			{
				union Converter
				{
					Converter(uint8_t* source) : mpSource(source) {}
					uint8_t* mpSource;
					ValueType* mpTarget;
				} convert(mSource);
				return convert.mpTarget;
			}
			const TYPE* Get() const
			{
				union Converter
				{
					Converter(const uint8_t* source) : mpSource(source) {}
					const uint8_t* mpSource;
					const ValueType* mpTarget;
				} convert(mSource);
				return convert.mpTarget;
			}

		private:
			uint8_t mSource[1];
		};

		//////////////////////////////////////////////////////////////////////////
		// The encoding/decoding structure for manipulating sector data.
		// TODO: This can use a bit of simd to avoid the bitfield pack/unpack.
		union SectorCodecI32x3
		{
			using SectorType = Vector3iv;
			using StorageType = float;
			static constexpr int BitsPerElement = 10;

			SectorCodecI32x3(const SectorType& s)
			{
				mFields.mX = s.x;
				mFields.mY = s.y;
				mFields.mZ = s.z;
			}
			SectorCodecI32x3(StorageType storage)
				: mStorage(storage)
			{
			}

			// Access the encoded data in three manners.
			struct 
			{
				// NOTE: Sign extension is going to be a bugger in simd.
				int32_t mX : BitsPerElement;
				int32_t mY : BitsPerElement;
				int32_t mZ : BitsPerElement;
			} mFields;
			StorageType mStorage;
		};

		//////////////////////////////////////////////////////////////////////////
		// The primitive data type which represents a large vector.
		struct alignas(16) LargeVector3fv_t
		{
			using StorageType = Vector4fv;
			using VectorType = Vector3fv;
			using SectorType = Vector3iv;
			using SectorCodec = SectorCodecI32x3;

			StorageType mData;
		};

		//////////////////////////////////////////////////////////////////////////
		// API to manipulate large vectors.
		template <typename TYPE>
		TYPE& Set(TYPE& largeVector, const typename TYPE::VectorType, const typename TYPE::SectorType);

		template <typename TYPE>
		typename TYPE::SectorType GetSector(const TYPE largeVector);
		template <typename TYPE>
		TYPE& SetSector(TYPE& largeVector, const typename TYPE::SectorType s);

		template <typename TYPE>
		typename TYPE::VectorType GetVector(const TYPE largeVector);
		template <typename TYPE>
		TYPE& SetVector(TYPE& largeVector, const typename TYPE::VectorType v);

		template <typename TYPE>
		TYPE GetSectorized(const TYPE& lv);

		template <typename TYPE>
		TYPE operator +(const TYPE& lhs, const typename TYPE::VectorType& rhs);
		template <typename TYPE>
		TYPE operator +(const TYPE& lhs, const TYPE& rhs);
		
		template <typename TYPE>
		TYPE operator -(const TYPE& lhs, const typename TYPE::VectorType& rhs);
		template <typename TYPE>
		TYPE operator -(const TYPE& lhs, const TYPE& rhs);

		// TODO: Should this bother with other operators?  Really shouldn't need to...
		

		//////////////////////////////////////////////////////////////////////////
		// High level wrapper around large vectors.
		// This throws a wrapper around the lower level type such that customization
		// is possible and some handy proxy utilities are possible.
		template <typename TYPE>
		union LargeVector3v
		{
		public:

		private:
			TYPE mLargeVector;
		};

		//////////////////////////////////////////////////////////////////////////
		using LargeVector3fv = LargeVector3v<LargeVector3fv_t>;
	}
}


#include "Detail/LargeVector.inl"

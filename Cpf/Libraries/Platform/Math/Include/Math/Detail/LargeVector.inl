//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		template <>
		void Set(LargeVector3fv_t& largeVector,
			const Vector3fv v,
			const Vector3iv s)
		{
			SectorCodec encode(s.x, s.y, s.z);
			union IntToFloat
			{
				IntToFloat(uint32_t v) : mSector(v) {}
				uint32_t mSector;
				float mStorage;
			} intToFloat(encode.mStorage);
			largeVector.mData = Vector4fv(v.xyz, intToFloat.mStorage);
		}

		template <>
		Vector3iv GetSector(const LargeVector3fv_t lg)
		{
			union FloatToInt
			{
				FloatToInt(float v) : mStorage(v) {}
				uint32_t mSector;
				float mStorage;
			} floatToInt(lg.mData.w);
			SectorCodec decode(floatToInt.mSector);
			return Vector3iv(decode.mFields.mX, decode.mFields.mY, decode.mFields.mZ);
		}

		template <>
		void SetSector(LargeVector3fv_t& largeVector, const Vector3iv s)
		{
			SectorCodec encode(s.x, s.y, s.z);
			union IntToFloat
			{
				IntToFloat(uint32_t v) : mSector(v) {}
				uint32_t mSector;
				float mStorage;
			} intToFloat(encode.mStorage);
			largeVector.mData = LargeVector3fv_t::StorageType(largeVector.mData.xyz, intToFloat.mStorage);
		}

		template <>
		LargeVector3fv_t::VectorType GetVector(const LargeVector3fv_t largeVector)
		{
			return LargeVector3fv_t::VectorType(largeVector.mData.xyz);
		}
		template <>
		void SetVector(LargeVector3fv_t& largeVector, const LargeVector3fv_t::VectorType v)
		{
			largeVector.mData = LargeVector3fv_t::StorageType(v.xyz, largeVector.mData.w);
		}


		template <>
		LargeVector3fv_t operator +(const LargeVector3fv_t& lhs, const LargeVector3fv_t& rhs)
		{
			LargeVector3fv_t result;
			Set(result, GetVector(lhs) + GetVector(rhs), GetSector(lhs) + GetSector(rhs));
			return result;
		}

		template <>
		LargeVector3fv_t operator -(const LargeVector3fv_t& lhs, const LargeVector3fv_t& rhs)
		{
			LargeVector3fv_t result;
			Set(result, GetVector(lhs) - GetVector(rhs), GetSector(lhs) - GetSector(rhs));
			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		typename TYPE::VectorType ExtractVector3(const TYPE& rhs);
		template <typename TYPE>
		void InsertVector(TYPE& dst, const typename TYPE::VectorType& value);

		template <typename TYPE>
		typename TYPE::SectorType ExtractSector(const TYPE& rhs);
		template <typename TYPE>
		void InsertSector(TYPE& dst, const typename TYPE::SectorType& value);

		template <typename TYPE>
		TYPE Normalize(const TYPE& value);

		template <typename TYPE>
		typename TYPE::SectorRep AsSectorRep(const TYPE& rhs);

		template <typename TYPE>
		typename TYPE::VectorType GetRelative(typename TYPE::SectorType from, const TYPE& to);

		template <typename TYPE>
		typename TYPE::VectorType GetRelative(const TYPE& from, const TYPE& to);

		void ElementNorm(const int32_t bound, float v, float& nv, int32_t& ns)
		{
			// Coordinate inclusion rules are for values to be less than
			// the sector size or more than or equal negative sector size.
			const int32_t bound2 = 2 * bound;
			if (v > bound)
			{
				ns = (int32_t(v) + bound) / bound2;
				nv = v - float(ns * bound2);
				return;
			}
			if (v <= -bound)
			{
				ns = (int32_t(v) - bound) / bound2;
				nv = float(-ns * bound2) + v;
				return;
			}

			nv = v;
			ns = 0;
		}

#if 0
		//////////////////////////////////////////////////////////////////////////
		// LargeVectorDesc_FI implementations.
		template <>
		LargeVector<LargeVectorDesc_FI> Normalize(const LargeVector<LargeVectorDesc_FI>& lv)
		{
			auto v = ExtractVector3(lv);
			int32_t xchange, ychange, zchange;
			float nx, ny, nz;
			NormalizeBounds(LargeVectorDesc_FI::HalfBound, v.x, nx, xchange);
			NormalizeBounds(LargeVectorDesc_FI::HalfBound, v.y, ny, ychange);
			NormalizeBounds(LargeVectorDesc_FI::HalfBound, v.z, nz, zchange);

			LargeVector<LargeVectorDesc_FI>::SectorType sector(ExtractSector(lv));
			sector.SetX(sector.GetX() + xchange);
			sector.SetY(sector.GetY() + ychange);
			sector.SetZ(sector.GetZ() + zchange);
			
			return LargeVector<LargeVectorDesc_FI>({nx, ny, nz}, sector);
		}

		template <>
		LargeVector<LargeVectorDesc_FI>::VectorType GetRelative(
			LargeVector<LargeVectorDesc_FI>::SectorType from,
			const LargeVector<LargeVectorDesc_FI>& to
		)
		{
			auto toSector = LargeVector<LargeVectorDesc_FI>::SectorRep(ExtractSector(to));
			auto delta = toSector - LargeVector<LargeVectorDesc_FI>::SectorRep(from);
			auto offset = delta * (LargeVectorDesc_FI::HalfBound * 2);
			return ExtractVector3(to) + LargeVector<LargeVectorDesc_FI>::VectorType(offset.xyz);
		}

		template <>
		LargeVectorDesc_FI::VectorType GetRelative(
			const LargeVector<LargeVectorDesc_FI>& from,
			const LargeVector<LargeVectorDesc_FI>& to
		)
		{
			auto relDelta = ExtractVector3(to) - ExtractVector3(from);
			auto relSector = LargeVector<LargeVectorDesc_FI>::SectorRep(ExtractSector(to)) -
				LargeVector<LargeVectorDesc_FI>::SectorRep(ExtractSector(from));
			return relDelta + LargeVector<LargeVectorDesc_FI>::VectorType((relSector * (LargeVectorDesc_FI::HalfBound*2)).xyz);
		}
#endif
	}
}

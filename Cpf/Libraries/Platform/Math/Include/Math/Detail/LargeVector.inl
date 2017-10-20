//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
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


		//////////////////////////////////////////////////////////////////////////
		// LargeVectorDesc_FI implementations.
		template <>
		LargeVectorDesc_FI::VectorType ExtractVector3(const LargeVector<LargeVectorDesc_FI>& lv)
		{
			// NOTE: Doesn't need to worry about removing the w component as the math
			// ignores it anyway.
			return LargeVectorDesc_FI::VectorType(LargeVectorDesc_FI::StorageType(lv).GetLanes<0, 1, 2>());
		}

		template <>
		void InsertVector(LargeVector<LargeVectorDesc_FI>& dst, const LargeVectorDesc_FI::VectorType& value)
		{
			float fsector = LargeVectorDesc_FI::StorageType(dst).GetLane<3>();
			// TODO: Renormalize the coordinates?
			SIMD::F32x4 simdValue(value.xyz, fsector);
			dst = LargeVector<LargeVectorDesc_FI>(simdValue);
		}

		template <>
		LargeVectorDesc_FI::SectorType ExtractSector(const LargeVector<LargeVectorDesc_FI>& lv)
		{
			float fsector = LargeVectorDesc_FI::StorageType(lv).GetLane<3>();
			return *reinterpret_cast<LargeVectorDesc_FI::SectorType*>(&fsector);
		}

		template <>
		void InsertSector(LargeVector<LargeVectorDesc_FI>& lv, const LargeVectorDesc_FI::SectorType& value)
		{
			SIMD::F32x4 simdValue(ExtractVector3(lv).xyz, *reinterpret_cast<const float*>(&value));
			lv = LargeVector<LargeVectorDesc_FI>(simdValue);
		}

		void NormalizeBounds(const int32_t bound, float v, float& nv, int32_t& ns)
		{
			// For consistency of behavior, the ownership rules are
			// that positive values are inclusive of the bound value while
			// negative values are exclusive.  I.e. the range of valid x
			// is "x > -bound && x<= bound".
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
			auto toSector = ExtractSector(to).AsRep();
			auto delta = toSector - from.AsRep();
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
			auto relSector = ExtractSector(to).AsRep() - ExtractSector(from).AsRep();
			return relDelta + LargeVector<LargeVectorDesc_FI>::VectorType((relSector * (LargeVectorDesc_FI::HalfBound*2)).xyz);
		}
	}
}

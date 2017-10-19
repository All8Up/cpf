//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		typename TYPE::PositionType ExtractPosition(const TYPE& rhs);
		template <typename TYPE>
		void InsertPosition(TYPE& dst, const typename TYPE::PositionType& value);

		template <typename TYPE>
		typename TYPE::SectorType ExtractSector(const TYPE& rhs);
		template <typename TYPE>
		void InsertSector(TYPE& dst, const typename TYPE::SectorType& value);

		template <typename TYPE>
		typename TYPE::SectorRep AsSectorRep(const TYPE& rhs);

		template <typename TYPE>
		typename TYPE::PositionType GetRelative(const TYPE& src, const TYPE& dst);

#if 0
		{
			// This is a re-arranged variation of the following:
			// (dst.position + dst.sector * halfBound) - (src.position + src.sector * halfBound);

			// 1- Build the integral offset values from the sectors.
			Vector3i offset = AsSectorRep(dst) - AsSectorRep(src);

			// 2- Convert integral offset into target vector type.
			Vector3f relative = Vector3f(offset * LARGEVECTOR::kSectorHalfBound);

			// 3- Add the relative position to the offset.
			return relative + (ExtractPosition(dst) - ExtractPosition(src));
		}
#endif
	}
}

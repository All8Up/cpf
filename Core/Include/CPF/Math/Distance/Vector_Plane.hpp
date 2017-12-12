//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		template <typename VTYPE, typename FTYPE = float>
		FTYPE Distance(const VTYPE v, const Plane<VTYPE, FTYPE>& p)
		{
			return Dot(v, p.Normal) - p.Distance;
		}
	}
}

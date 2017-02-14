//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Time.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace Time
		{
			/**
			 * @brief Utility class to represent ratios.
			 */
			class CPF_EXPORT_TIME Ratio
			{
			public:
				// Construction.
				Ratio();
				Ratio(int64_t numerator, int64_t denominator);

				// Accessors.
				void SetNumerator(int64_t value);
				int64_t GetNumerator() const;
				void SetDenominator(int64_t value);
				int64_t GetDenominator() const;

			private:
				// Implementation data.
				int64_t m_Numerator;
				int64_t m_Denominator;
			};
		}
	}
}

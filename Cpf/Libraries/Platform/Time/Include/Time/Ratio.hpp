//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Time
	{
		/**
		 * @brief Utility class to represent ratios.
		 */
		class Ratio
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


		/** @brief Default constructor. */
		inline Ratio::Ratio()
			: m_Numerator(0)
			, m_Denominator(0)
		{}

		/**
		* @brief Construct a ratio.
		* @param numerator The numerator used in the ratio.
		* @param denominator The denominator used in the ratio.
		*/
		inline Ratio::Ratio(int64_t numerator, int64_t denominator)
			: m_Numerator(numerator)
			, m_Denominator(denominator)
		{
			CPF_ASSERT(numerator != 0);
			CPF_ASSERT(denominator != 0);
		}

		/**
		* @brief Set the numerator of the ratio.
		*/
		inline void Ratio::SetNumerator(int64_t value)
		{
			CPF_ASSERT(value != 0);
			m_Numerator = value;
		}

		/**
		* @brief Get the numerator from the ratio.
		*/
		inline int64_t Ratio::GetNumerator() const
		{
			return m_Numerator;
		}

		/**
		* @brief Set the denominator of the ratio.
		*/
		inline void Ratio::SetDenominator(int64_t value)
		{
			CPF_ASSERT(value != 0);
			m_Denominator = value;
		}

		/**
		* @brief Get the denominator from the ratio.
		*/
		inline int64_t Ratio::GetDenominator() const
		{
			return m_Denominator;
		}
	}
}

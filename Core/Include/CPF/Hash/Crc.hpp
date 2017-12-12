//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Hash/Detail/Crc15Table.hpp"
#include "CPF/Hash/Detail/Crc16Table.hpp"
#include "CPF/Hash/Detail/Crc32Table.hpp"
#include "CPF/Hash/Detail/Crc64Table.hpp"


namespace CPF
{
	namespace Hash
	{
		/**
		 * @brief Compute a 15 bit crc recursively for compile time results.
		 */
		constexpr uint16_t ComputeCrc15(const char* data, size_t idx, uint16_t crc)
		{
			return idx == 0 ? (~crc & 0x7fff)
				: ComputeCrc15(&data[1], idx - 1, Detail::Crc15Table[(crc ^ data[0]) & 0xFF] ^ (crc >> 7));
		}

		/**
		 * @brief Compute a 16 bit crc recursively for compile time results.
		 */
		constexpr uint16_t ComputeCrc16(const char* data, size_t idx, uint16_t crc)
		{
			return idx == 0 ? ~crc
				: ComputeCrc16(&data[1], idx - 1, Detail::Crc16Table[(crc ^ data[0]) & 0xFF] ^ (crc >> 8));
		}


		/**
		* @brief Compute a 32 bit crc recursively for compile time results.
		*/
		constexpr uint32_t ComputeCrc32(const char* data, size_t idx, uint32_t crc)
		{
			return idx == 0 ? ~crc
				: ComputeCrc32(&data[1], idx - 1, Detail::Crc32Table[(crc ^ data[0]) & 0xFF] ^ (crc >> 8));
		}


		/**
		* @brief Compute a 64 bit crc recursively for compile time results.
		*/
		constexpr uint64_t ComputeCrc64(const char* data, size_t idx, uint64_t crc)
		{
			return idx == 0 ? ~crc
				: ComputeCrc64(&data[1], idx - 1, Detail::Crc64Table[(crc ^ data[0]) & 0xFF] ^ (crc >> 8));
		}


		/**
		 * @brief Updates the crc with more data.
		 */
		inline uint16_t UpdateCrc15(uint16_t crc, const uint8_t* data, size_t length)
		{
			while (length--)
				crc = Detail::Crc15Table[(crc ^ *data++) & 0xFFL] ^ (crc >> 7);
			return crc & 0x7fff;
		}

		/**
		 * @brief Updates the crc with more data.
		 */
		inline uint16_t UpdateCrc16(uint16_t crc, const uint8_t* data, size_t length)
		{
			while (length--)
				crc = Detail::Crc16Table[(crc ^ *data++) & 0xFFL] ^ (crc >> 8);
			return crc;
		}


		/**
		 * @brief Finalizes the crc.
		 */
		constexpr uint16_t FinalizeCrc16(uint16_t crc)
		{
			return crc ^ -1;
		}


		/**
		 * @brief Compute a 15 bit crc from the given data.
		 */
		constexpr uint16_t Crc15(const char* const data, size_t length)
		{
			return ComputeCrc15(data, length, uint16_t(0));
		}


		/**
		 * @brief Compute a 32 bit crc from the given data.
		 */
		constexpr uint16_t Crc16(const char* const data, size_t length)
		{
			return ComputeCrc16(data, length, uint16_t(-1));
		}


		/**
		 * @brief Updates the crc with more data.
		 */
		inline uint32_t UpdateCrc32(uint32_t crc, const uint8_t* data, size_t length)
		{
			while (length--)
				crc = Detail::Crc32Table[(crc ^ *data++) & 0xFFL] ^ (crc >> 8);
			return crc;
		}


		/**
		 * @brief Finalizes the crc.
		 */
		constexpr uint32_t FinalizeCrc32(uint32_t crc)
		{
			return crc ^ -1;
		}


		/**
		 * @brief Compute a 32 bit crc from the given data.
		 */
		constexpr uint32_t Crc32(const char* const data, size_t length)
		{
			return ComputeCrc32(data, length, uint32_t(-1));
		}


		/**
		 * @brief Updates the crc with more data.
		 */
		inline uint64_t UpdateCrc64(uint64_t crc, const uint8_t* data, size_t length)
		{
			while (length--)
				crc = Detail::Crc64Table[(crc ^ *data++) & 0xFFL] ^ (crc >> 8);
			return crc;
		}


		/**
		* @brief Finalizes the crc.
		*/
		constexpr uint64_t FinalizeCrc64(uint64_t crc)
		{
			return crc ^ -1;
		}


		/**
		* @brief Compute a 64 bit crc from the given data.
		*/
		constexpr uint64_t Crc64(const char* const data, size_t length)
		{
			return ComputeCrc64(data, length, uint64_t(-1));
		}
	}
}

/**
 * @brief String literal crc15 computation.
 */
constexpr uint16_t operator "" _crc15(const char* val, size_t idx)
{
	return CPF::Hash::ComputeCrc15(val, idx, uint16_t(0));
}


/**
 * @brief String literal crc16 computation.
 */
constexpr uint16_t operator "" _crc16(const char* val, size_t idx)
{
	return CPF::Hash::ComputeCrc16(val, idx, uint16_t(-1));
}


/**
 * @brief String literal crc32 computation.
 */
constexpr uint32_t operator "" _crc32(const char* val, size_t idx)
{
	return CPF::Hash::ComputeCrc32(val, idx, uint32_t(-1));
}


/**
* @brief String literal crc64 computation.
*/
constexpr uint64_t operator "" _crc64(const char* val, size_t idx)
{
	return CPF::Hash::ComputeCrc64(val, idx, uint64_t(-1));
}

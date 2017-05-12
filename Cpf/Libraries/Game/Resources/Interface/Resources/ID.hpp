//////////////////////////////////////////////////////////////////////////
#pragma once
#include "String.hpp"
#include "Hash/Crc.hpp"

namespace Cpf
{
	namespace Resources
	{
		static constexpr uint64_t kInvalidID = uint64_t(-1);

		struct ID
		{
			ID(uint32_t d, uint32_t f
#ifdef CPF_DEBUG
			, const char* const dirName,
			const char* const fileName
#endif
			) : mDirectory(d), mFile(f)
#ifdef CPF_DEBUG
			, mpDirectory(dirName)
			, mpFilename(fileName)
#endif
			{}
			explicit ID(uint64_t id) : mID(id)
#ifdef CPF_DEBUG
			, mpDirectory(nullptr)
			, mpFilename(nullptr)
#endif
			{}

			union
			{
				struct
				{
					uint32_t mDirectory;
					uint32_t mFile;
					uint32_t mType;
				};
				uint64_t mID;
				uint64_t mOther; // Temporary padding, this is supposed to be a 128 bit structure eventually
			};

#ifdef CPF_DEBUG
			const String ToString() const {return String(mpDirectory) + String(mpFilename);}

			const char* const mpDirectory;
			const char* const mpFilename;
#else
			const String ToString() const {return String();}
#endif
		};
	}
}

// Utility macro to create an ID at compile time.
#ifdef CPF_DEBUG
#	define RESOURCE_ID(d, f)				\
		Cpf::Resources::ID { d##_crc32, f##_crc32, d, f }
#else
#	define RESOURCE_ID(d, f)				\
		Cpf::Resources::ID { d##_crc32, f##_crc32 }
#endif

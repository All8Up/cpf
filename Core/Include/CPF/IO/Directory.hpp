//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"
#include "CPF/Std/Utf8String.hpp"
#include "CPF/Std/Functional.hpp"
#include "CPF/IO/Attributes.hpp"
#include "CPF/Option.hpp"

namespace CPF
{
	namespace IO
	{
		namespace Directory
		{
			CPF_EXPORT void SetWorkingDirectory(const STD::Utf8String&);
			CPF_EXPORT STD::Utf8String GetWorkingDirectory();

			CPF_EXPORT bool OsExists(const STD::Utf8String& dir);
			CPF_EXPORT bool OsCreate(const STD::Utf8String& dir);
			CPF_EXPORT bool OsDelete(const STD::Utf8String& dir);

			CPF_EXPORT Option<char*> OsGetError();
			CPF_EXPORT void OsFreeError(char*);

			CPF_EXPORT bool Exists(const STD::Utf8String& dir);
			CPF_EXPORT bool Create(const STD::Utf8String& dir, bool recursive = false);
			CPF_EXPORT bool Delete(const STD::Utf8String& dir, bool recursive = false);

			//
			struct DirEntry
			{
				STD::Utf8String mName;
				Attributes mAttributes;
			};

			/** @brief Iterates all entries found within a given directory.. */
			class CPF_EXPORT Entries
			{
				//
				struct OsIterator;

			public:
				//
				using Predicate = STD::Function<bool(const DirEntry&)>;

				//
				class CPF_EXPORT Iterator
				{
				public:
					Iterator();
					Iterator(const STD::Utf8String& path, Predicate&& pred);
					Iterator(Iterator&& rhs) noexcept;
					~Iterator();

					bool operator !=(const Iterator& rhs) const;
					Iterator& operator ++();
					DirEntry operator *() const;

				private:
					Iterator(const Iterator&) = delete;
					Iterator& operator =(const Iterator&) = delete;

					OsIterator* mpIterator;
				};

				//
				Entries(const STD::Utf8String& path);
				Entries(const STD::Utf8String& path, Predicate&& pred);

				Iterator begin();
				Iterator end();

			private:
				CPF_DLL_SAFE_BEGIN;
				STD::Utf8String mPath;
				Predicate mPredicate;
				CPF_DLL_SAFE_END;
			};

			/** @brief Iterates all files found in a given directory. */
			class CPF_EXPORT Files : public Entries
			{
			public:
				Files(const STD::Utf8String& path);
				Files(const STD::Utf8String& path, Predicate&& pred);
			};

			/** @brief Iterates all subdirectories found in a given directory. */
			class CPF_EXPORT Directories : public Entries
			{
			public:
				Directories(const STD::Utf8String& path);
				Directories(const STD::Utf8String& path, Predicate&& pred);
			};
		}
	}
}

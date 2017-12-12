//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/Std/Functional.hpp"
#include "CPF/IO/Attributes.hpp"

namespace CPF
{
	namespace IO
	{
		namespace Directory
		{
			CPF_EXPORT void SetWorkingDirectory(const String&);
			CPF_EXPORT String GetWorkingDirectory();

			CPF_EXPORT bool OsExists(const String& dir);
			CPF_EXPORT bool OsCreate(const String& dir);
			CPF_EXPORT bool OsDelete(const String& dir);

			CPF_EXPORT bool Exists(const String& dir);
			CPF_EXPORT bool Create(const String& dir, bool recursive = false);
			CPF_EXPORT bool Delete(const String& dir, bool recursive = false);

			//
			struct DirEntry
			{
				String mName;
				Attributes mAttributes;
			};

			/** @brief Iterates all entries found within a given directory.. */
			class CPF_EXPORT Entries
			{
				//
				struct OsIterator;

			public:
				//
				using Predicate = Function<bool(const DirEntry&)>;

				//
				class CPF_EXPORT Iterator
				{
				public:
					Iterator();
					Iterator(const String& path, Predicate&& pred);
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
				Entries(const String& path);
				Entries(const String& path, Predicate&& pred);

				Iterator begin();
				Iterator end();

			private:
				CPF_DLL_SAFE_BEGIN;
				String mPath;
				Predicate mPredicate;
				CPF_DLL_SAFE_END;
			};

			/** @brief Iterates all files found in a given directory. */
			class CPF_EXPORT Files : public Entries
			{
			public:
				Files(const String& path);
				Files(const String& path, Predicate&& pred);
			};

			/** @brief Iterates all subdirectories found in a given directory. */
			class CPF_EXPORT Directories : public Entries
			{
			public:
				Directories(const String& path);
				Directories(const String& path, Predicate&& pred);
			};
		}
	}
}

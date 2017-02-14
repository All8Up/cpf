//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "IO/IO.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Functional.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			namespace Directory
			{
				CPF_EXPORT_IO void SetWorkingDirectory(const String&);
				CPF_EXPORT_IO String GetWorkingDirectory();

				CPF_EXPORT_IO bool OsExists(const String& dir);
				CPF_EXPORT_IO bool OsCreate(const String& dir);
				CPF_EXPORT_IO bool OsDelete(const String& dir);

				CPF_EXPORT_IO bool Exists(const String& dir);
				CPF_EXPORT_IO bool Create(const String& dir, bool recursive = false);
				CPF_EXPORT_IO bool Delete(const String& dir, bool recursive = false);

				//
				enum Attributes : uint32_t
				{
					eFile = 1 << 0,
					eDirectory = 1 << 1,
					eSymlink = 1 << 2
				};
				struct DirEntry
				{
					String mName;
					uint32_t mAttributes;
				};

				/** @brief Iterates all entries found within a given directory.. */
				class CPF_EXPORT_IO Entries
				{
					//
					struct OsIterator;

				public:
					//
					using Predicate = Function<bool(const DirEntry&)>;

					//
					class CPF_EXPORT_IO Iterator
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
				class CPF_EXPORT_IO Files : public Entries
				{
				public:
					Files(const String& path);
					Files(const String& path, Predicate&& pred);
				};

				/** @brief Iterates all subdirectories found in a given directory. */
				class CPF_EXPORT_IO Directories : public Entries
				{
				public:
					Directories(const String& path);
					Directories(const String& path, Predicate&& pred);
				};
			}
		}
	}
}

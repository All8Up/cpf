//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "Platform/SharedLibrary.hpp"

namespace CPF
{
	namespace Plugin
	{
		/** @brief A general purpose shared library maintainer. */
		class CPF_EXPORT Library : public CPF::tRefCounted<>
		{
		public:
			/** @brief Default constructor. */
			Library();

			/**
			 * @brief Move constructor.
			 * @param [in,out] rhs The source library.
			 */
			Library(Library&& rhs);
			/** @brief Destructor. */
			~Library();

			/**
			 * @brief Loads the given library.
			 * @param name The path and name of the library to load.
			 * @return True if it loads, false if there is an error.
			 */
			bool Load(const char* const name);

			/**
			 * @brief Unloads the library.
			 * @return True if it succeeds, false if it fails.
			 */
			bool Unload();

			/**
			 * @brief Checks the status of the library.
			 * @return If the library is loaded or not.
			 */
			operator bool() const;

			/**
			 * @brief Gets the address of an exported symbol.
			 * @param symbol Name of the symbol to find.
			 * @return The address of the symbol.
			 */
			void* GetAddress(const char* const symbol);

			/**
			 * @brief Gets the address of an exported symbol and cast it to the given type.
			 * @param symbol The symbol name.
			 * @return The address of the symbol.
			 */
			template <typename FUNCTYPE>
			FUNCTYPE GetAddress(const char* const symbol)
			{
				return reinterpret_cast<FUNCTYPE>(GetAddress(symbol));
			}

		private:
			// Move only object.
			Library(const Library&) = delete;
			Library& operator = (const Library&) = delete;

			// Handle to the library.
			Platform::Library::Handle mHandle;
		};


		//////////////////////////////////////////////////////////////////////////

		inline Library::Library()
			: mHandle(Platform::Library::kInvalid)
		{
		}

		inline Library::Library(Library&& rhs)
			: mHandle(rhs.mHandle)
		{
			rhs.mHandle = Platform::Library::kInvalid;
		}

		inline Library::~Library()
		{
			if (mHandle!=Platform::Library::kInvalid)
				Platform::Library::Free(mHandle);
		}

		inline bool Library::Load(const char* const name)
		{
			mHandle = Platform::Library::Load(name);
#ifndef CPF_FINAL_BUILD
			if (mHandle == Platform::Library::kInvalid)
			{
				// May be a unit test or running from inside the bin folder, try again with appropriate prepend.
				char tempBuffer[1024];
				strcpy(tempBuffer, "./../resources/");
				strcat(tempBuffer, name);
				mHandle = Platform::Library::Load(tempBuffer);
			}
#endif
			return mHandle != Platform::Library::kInvalid;
		}

		inline bool Library::Unload()
		{
			if (mHandle != Platform::Library::kInvalid)
			{
				Platform::Library::Free(mHandle);
				mHandle = Platform::Library::kInvalid;
				return true;
			}
			return false;
		}

		inline Library::operator bool() const
		{
			return mHandle != Platform::Library::kInvalid;
		}

		inline void* Library::GetAddress(const char* const symbol)
		{
			if (mHandle != Platform::Library::kInvalid)
				return Platform::Library::GetAddress(mHandle, symbol);
			return nullptr;
		}
	}
}

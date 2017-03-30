//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "Platform/SharedLibrary.hpp"

namespace Cpf
{
	namespace Plugin
	{
		class CPF_EXPORT Library : public tRefCounted<>
		{
		public:
			Library();
			~Library();

			bool Load(const char* const name);
			bool Unload();

			operator bool() const;

			void* GetAddress(const char* const symbol);
			template <typename FUNCTYPE>
			FUNCTYPE GetAddress(const char* const symbol)
			{
				return reinterpret_cast<FUNCTYPE>(GetAddress(symbol));
			}

		private:
			Platform::Library::Handle mHandle;
		};


		//////////////////////////////////////////////////////////////////////////

		inline Library::Library()
			: mHandle(Platform::Library::kInvalid)
		{
		}

		inline Library::~Library()
		{
			if (mHandle!=Platform::Library::kInvalid)
				Platform::Library::Free(mHandle);
		}

		inline bool Library::Load(const char* const name)
		{
			mHandle = Platform::Library::Load(name);
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

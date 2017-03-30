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
			Library(const char* const name);
			~Library();

			operator bool() const;

			void* GetAddress(const char* const symbol);

		private:
			Platform::Library::Handle mHandle;
		};


		//////////////////////////////////////////////////////////////////////////

		inline Library::Library(const char* const name)
			: mHandle(Platform::Library::Load(name))
		{
		}

		inline Library::~Library()
		{
			if (mHandle!=Platform::Library::kInvalid)
				Platform::Library::Free(mHandle);
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

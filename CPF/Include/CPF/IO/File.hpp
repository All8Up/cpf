/**
* @brief Declares the file class.
*/
#pragma once
#include "CPF/IO.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/IO/Stream.hpp"

namespace CPF
{
	namespace IO
	{
		namespace File
		{
			CPF_EXPORT bool Exists(const String& name);
			CPF_EXPORT bool Exists(const WString& name);
			CPF_EXPORT bool Delete(const String& name);
			CPF_EXPORT bool Delete(const WString& name);
			/*
			CPF_EXPORT bool Move(const String& src, const String& dst);
			CPF_EXPORT bool Move(const WString& src, const WString& dst);
			CPF_EXPORT bool Copy(const String& src, const String& dst);
			CPF_EXPORT bool Copy(const WString& src, const WString& dst);
			CPF_EXPORT int64_t GetLength(const String& name);
			CPF_EXPORT int64_t GetLength(const WString& name);
			CPF_EXPORT uint32_t GetAttributes(const String& name);
			CPF_EXPORT uint32_t GetAttributes(const WString& name);
			 */

			CPF_EXPORT Stream* Create(const String& name, Access access, Error* error = nullptr);

			String CPF_EXPORT GetExecutableFilePath();
		}
	}
}

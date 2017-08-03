/**
* @brief Declares the file class.
*/
#pragma once
#include "IO/IO.hpp"
#include "String.hpp"
#include "Stream.hpp"

namespace Cpf
{
	namespace IO
	{
		namespace File
		{
			CPF_EXPORT_IO bool Exists(const String& name);
			CPF_EXPORT_IO bool Exists(const WString& name);
			CPF_EXPORT_IO bool Delete(const String& name);
			CPF_EXPORT_IO bool Delete(const WString& name);
			/*
			CPF_EXPORT_IO bool Move(const String& src, const String& dst);
			CPF_EXPORT_IO bool Move(const WString& src, const WString& dst);
			CPF_EXPORT_IO bool Copy(const String& src, const String& dst);
			CPF_EXPORT_IO bool Copy(const WString& src, const WString& dst);
			CPF_EXPORT_IO int64_t GetLength(const String& name);
			CPF_EXPORT_IO int64_t GetLength(const WString& name);
			CPF_EXPORT_IO uint32_t GetAttributes(const String& name);
			CPF_EXPORT_IO uint32_t GetAttributes(const WString& name);
			 */

			CPF_EXPORT_IO Stream* Create(const String& name, StreamAccess access, Error* error = nullptr);

			String CPF_EXPORT_IO GetExecutableFilePath();
		}
	}
}

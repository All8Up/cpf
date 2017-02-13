//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"
#include <cstdio>

namespace Cpf
{
	// TODO: Should this correct the argument orders for consistency unlike the standard?
	//	I.e. FILE* as the first argument in all functions which use it.
	namespace Std
	{
		using FILE = ::FILE;

		CPF_EXPORT_STD int Remove(const char* fname);
		CPF_EXPORT_STD int Rename(const char* oldname, const char* newname);
		CPF_EXPORT_STD FILE* TmpFile();
		CPF_EXPORT_STD char* TmpNam(char* str);

		CPF_EXPORT_STD int FClose(FILE* f);
		CPF_EXPORT_STD int FFlush(FILE* f);
		CPF_EXPORT_STD FILE* FOpen(const char* fname, const char* mode);
		CPF_EXPORT_STD FILE* FReOpen(const char* fname, const char* mode, FILE* stream);
		CPF_EXPORT_STD void SetBuf(FILE* f, char* buffer);
		CPF_EXPORT_STD int SetVBuf(FILE* f, char* buffer, int mode, size_t size);

		CPF_EXPORT_STD int FPrintF(FILE* f, const char* format, ...);
		CPF_EXPORT_STD int FScanF(FILE* f, const char* format, ...);
		CPF_EXPORT_STD int PrintF(const char* format, ...);
		CPF_EXPORT_STD int ScanF(const char* format, ...);
		template<typename... ARGS>
		int SnPrintF(char* s, size_t n, const char* format, ARGS... args)
		{
			return snprintf(s, n, format, args...);
		}
		CPF_EXPORT_STD int SprintF(char* s, const char* format, ...);
		CPF_EXPORT_STD int SScanF(const char* s, const char* format, ...);
		CPF_EXPORT_STD int VfPrintF(FILE* f, const char* format, va_list args);
		CPF_EXPORT_STD int VfScanF(FILE* f, const char* format, va_list args);
		CPF_EXPORT_STD int VPrintF(const char* format, va_list args);
		CPF_EXPORT_STD int VScanF(const char* format, va_list args);
		CPF_EXPORT_STD int VsnPrintF(char* s, size_t n, const char* format, va_list args);
		CPF_EXPORT_STD int VSprintF(char* s, const char* format, va_list args);
		CPF_EXPORT_STD int VsScanF(const char* s, const char* format, va_list args);

		CPF_EXPORT_STD int FGetC(FILE* f);
		CPF_EXPORT_STD char* FGetS(char* str, int num, FILE* stream);
		CPF_EXPORT_STD int FPutC(int c, FILE* stream);
		CPF_EXPORT_STD int FPutS(const char* std, FILE* stream);
		CPF_EXPORT_STD int GetC(FILE* stream);
		CPF_EXPORT_STD int GetChar();
//		CPF_EXPORT_STD char* GetS(char* str);
		CPF_EXPORT_STD int PutC(int c, FILE* stream);
		CPF_EXPORT_STD int PutChar(int c);
		CPF_EXPORT_STD int PutS(const char* str);
		CPF_EXPORT_STD int UngetC(int c, FILE* stream);

		CPF_EXPORT_STD size_t FRead(void* ptr, size_t size, size_t count, FILE* stream);
		CPF_EXPORT_STD size_t FWrite(const void* ptr, size_t size, size_t count, FILE* stream);

		CPF_EXPORT_STD int FGetPos(FILE* stream, fpos_t* pos);
		CPF_EXPORT_STD int FSeek(FILE* stream, long int offset, int origin);
		CPF_EXPORT_STD int FSetPos(FILE* stream, const fpos_t* pos);
		CPF_EXPORT_STD long int FTell(FILE* stream);
		CPF_EXPORT_STD void Rewind(FILE* stream);

		CPF_EXPORT_STD void ClearErr(FILE* stream);
		CPF_EXPORT_STD int FEof(FILE* stream);
		CPF_EXPORT_STD int FError(FILE* stream);
		CPF_EXPORT_STD void PError(const char* str);
	}
}

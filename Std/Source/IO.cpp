//////////////////////////////////////////////////////////////////////////
#include "Std/IO.hpp"
#include <cstdarg>

using namespace Cpf;

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD int Std::Remove(const char* fname)
{
	return remove(fname);
}

CPF_EXPORT_STD int Std::Rename(const char* oldname, const char* newname)
{
	return rename(oldname, newname);
}

CPF_EXPORT_STD FILE* Std::TmpFile()
{
	return tmpfile();
}

CPF_EXPORT_STD char* Std::TmpNam(char* str)
{
	return tmpnam(str);
}


//////////////////////////////////////////////////////////////////////////

CPF_EXPORT_STD int Std::FClose(FILE* f)
{
	return fclose(f);
}

CPF_EXPORT_STD int Std::FFlush(FILE* f)
{
	return fflush(f);
}

CPF_EXPORT_STD FILE* Std::FOpen(const char* fname, const char* mode)
{
	return fopen(fname, mode);
}

CPF_EXPORT_STD FILE* Std::FReOpen(const char* fname, const char* mode, FILE* stream)
{
	return freopen(fname, mode, stream);
}

CPF_EXPORT_STD void Std::SetBuf(FILE* f, char* buffer)
{
	setbuf(f, buffer);
}

CPF_EXPORT_STD int Std::SetVBuf(FILE* f, char* buffer, int mode, size_t size)
{
	return setvbuf(f, buffer, mode, size);
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD int Std::FPrintF(FILE* f, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vfprintf(f, format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::FScanF(FILE* f, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vfscanf(f, format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::PrintF(const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vprintf(format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::ScanF(const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vscanf(format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::SprintF(char* s, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vsprintf(s, format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::SScanF(const char* s, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	int result = vsscanf(s, format, argp);
	va_end(argp);
	return result;
}

CPF_EXPORT_STD int Std::VfPrintF(FILE* f, const char* format, va_list args)
{
	return vfprintf(f, format, args);
}

CPF_EXPORT_STD int Std::VfScanF(FILE* f, const char* format, va_list args)
{
	return vfscanf(f, format, args);
}

CPF_EXPORT_STD int Std::VPrintF(const char* format, va_list args)
{
	return vprintf(format, args);
}

CPF_EXPORT_STD int Std::VScanF(const char* format, va_list args)
{
	return vscanf(format, args);
}

CPF_EXPORT_STD int Std::VsnPrintF(char* s, size_t n, const char* format, va_list args)
{
	return vsnprintf(s, n, format, args);
}

CPF_EXPORT_STD int Std::VSprintF(char* s, const char* format, va_list args)
{
	return vsprintf(s, format, args);
}

CPF_EXPORT_STD int Std::VsScanF(const char* s, const char* format, va_list args)
{
	return vsscanf(s, format, args);
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD int Std::FGetC(FILE* f)
{
	return fgetc(f);
}

CPF_EXPORT_STD char* Std::FGetS(char* str, int num, FILE* stream)
{
	return fgets(str, num, stream);
}

CPF_EXPORT_STD int Std::FPutC(int c, FILE* stream)
{
	return fputc(c, stream);
}

CPF_EXPORT_STD int Std::FPutS(const char* std, FILE* stream)
{
	return fputs(std, stream);
}

CPF_EXPORT_STD int Std::GetC(FILE* stream)
{
	return getc(stream);
}

CPF_EXPORT_STD int Std::GetChar()
{
	return getchar();
}

/* TODO: Doesn't seem to exist in Windows....
CPF_EXPORT_STD char* Std::GetS(char* str)
{
	return gets(str);
}
*/

CPF_EXPORT_STD int Std::PutC(int c, FILE* stream)
{
	return putc(c, stream);
}

CPF_EXPORT_STD int Std::PutChar(int c)
{
	return putchar(c);
}

CPF_EXPORT_STD int Std::PutS(const char* str)
{
	return puts(str);
}

CPF_EXPORT_STD int Std::UngetC(int c, FILE* stream)
{
	return ungetc(c, stream);
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD size_t Std::FRead(void* ptr, size_t size, size_t count, FILE* stream)
{
	return fread(ptr, size, count, stream);
}

CPF_EXPORT_STD size_t Std::FWrite(const void* ptr, size_t size, size_t count, FILE* stream)
{
	return fwrite(ptr, size, count, stream);
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD int Std::FGetPos(FILE* stream, fpos_t* pos)
{
	return fgetpos(stream, pos);
}

CPF_EXPORT_STD int Std::FSeek(FILE* stream, long int offset, int origin)
{
	return fseek(stream, offset, origin);
}

CPF_EXPORT_STD int Std::FSetPos(FILE* stream, const fpos_t* pos)
{
	return fsetpos(stream, pos);
}

CPF_EXPORT_STD long int Std::FTell(FILE* stream)
{
	return ftell(stream);
}

CPF_EXPORT_STD void Std::Rewind(FILE* stream)
{
	rewind(stream);
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_STD void Std::ClearErr(FILE* stream)
{
	clearerr(stream);
}

CPF_EXPORT_STD int Std::FEof(FILE* stream)
{
	return feof(stream);
}

CPF_EXPORT_STD int Std::FError(FILE* stream)
{
	return ferror(stream);
}

CPF_EXPORT_STD void Std::PError(const char* str)
{
	perror(str);
}

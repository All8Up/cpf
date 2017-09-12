//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Std/Std.hpp"
#include <cstdio>
#include <cstdarg>

namespace CPF
{
	namespace Std
	{
		using FILE = ::FILE;

		//////////////////////////////////////////////////////////////////////////
		inline int Remove(const char* fname)
		{
			return remove(fname);
		}

		inline int Rename(const char* oldname, const char* newname)
		{
			return rename(oldname, newname);
		}

		inline FILE* TmpFile()
		{
			return tmpfile();
		}

		inline char* TmpNam(char* str)
		{
			return tmpnam(str);
		}


		//////////////////////////////////////////////////////////////////////////

		inline int FClose(FILE* f)
		{
			return fclose(f);
		}

		inline int FFlush(FILE* f)
		{
			return fflush(f);
		}

		inline FILE* FOpen(const char* fname, const char* mode)
		{
			return fopen(fname, mode);
		}

		inline FILE* FReOpen(FILE* stream, const char* fname, const char* mode)
		{
			return freopen(fname, mode, stream);
		}

		inline void SetBuf(FILE* f, char* buffer)
		{
			setbuf(f, buffer);
		}

		inline int SetVBuf(FILE* f, char* buffer, int mode, size_t size)
		{
			return setvbuf(f, buffer, mode, size);
		}

		//////////////////////////////////////////////////////////////////////////
		inline int FPrintF(FILE* f, const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vfprintf(f, format, argp);
			va_end(argp);
			return result;
		}

		inline int FScanF(FILE* f, const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vfscanf(f, format, argp);
			va_end(argp);
			return result;
		}

		inline int PrintF(const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vprintf(format, argp);
			va_end(argp);
			return result;
		}

		inline int ScanF(const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vscanf(format, argp);
			va_end(argp);
			return result;
		}

		inline int SprintF(char* s, const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vsprintf(s, format, argp);
			va_end(argp);
			return result;
		}

		inline int SScanF(const char* s, const char* format, ...)
		{
			va_list argp;
			va_start(argp, format);
			int result = vsscanf(s, format, argp);
			va_end(argp);
			return result;
		}

		inline int VfPrintF(FILE* f, const char* format, va_list args)
		{
			return vfprintf(f, format, args);
		}

		inline int VfScanF(FILE* f, const char* format, va_list args)
		{
			return vfscanf(f, format, args);
		}

		inline int VPrintF(const char* format, va_list args)
		{
			return vprintf(format, args);
		}

		inline int VScanF(const char* format, va_list args)
		{
			return vscanf(format, args);
		}

		inline int VsnPrintF(char* s, size_t n, const char* format, va_list args)
		{
			return vsnprintf(s, n, format, args);
		}

		inline int VSprintF(char* s, const char* format, va_list args)
		{
			return vsprintf(s, format, args);
		}

		inline int VsScanF(const char* s, const char* format, va_list args)
		{
			return vsscanf(s, format, args);
		}

		//////////////////////////////////////////////////////////////////////////
		inline int FGetC(FILE* f)
		{
			return fgetc(f);
		}

		inline char* FGetS(FILE* stream, char* str, int num)
		{
			return fgets(str, num, stream);
		}

		inline int FPutC(FILE* stream, int c)
		{
			return fputc(c, stream);
		}

		inline int FPutS(FILE* stream, const char* std)
		{
			return fputs(std, stream);
		}

		inline int GetC(FILE* stream)
		{
			return getc(stream);
		}

		inline int GetChar()
		{
			return getchar();
		}

		/* TODO: Doesn't seem to exist in Windows....
		inline char* GetS(char* str)
		{
		return gets(str);
		}
		*/

		inline int PutC(FILE* stream, int c)
		{
			return putc(c, stream);
		}

		inline int PutChar(int c)
		{
			return putchar(c);
		}

		inline int PutS(const char* str)
		{
			return puts(str);
		}

		inline int UngetC(FILE* stream, int c)
		{
			return ungetc(c, stream);
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t FRead(FILE* stream, void* ptr, size_t size, size_t count)
		{
			return fread(ptr, size, count, stream);
		}

		inline size_t FWrite(FILE* stream, const void* ptr, size_t size, size_t count)
		{
			return fwrite(ptr, size, count, stream);
		}

		//////////////////////////////////////////////////////////////////////////
		inline int FGetPos(FILE* stream, fpos_t* pos)
		{
			return fgetpos(stream, pos);
		}

		inline int FSeek(FILE* stream, long int offset, int origin)
		{
			return fseek(stream, offset, origin);
		}

		inline int FSetPos(FILE* stream, const fpos_t* pos)
		{
			return fsetpos(stream, pos);
		}

		inline long int FTell(FILE* stream)
		{
			return ftell(stream);
		}

		inline void Rewind(FILE* stream)
		{
			rewind(stream);
		}

		//////////////////////////////////////////////////////////////////////////
		inline void ClearErr(FILE* stream)
		{
			clearerr(stream);
		}

		inline int FEof(FILE* stream)
		{
			return feof(stream);
		}

		inline int FError(FILE* stream)
		{
			return ferror(stream);
		}

		inline void PError(const char* str)
		{
			perror(str);
		}
	}
}

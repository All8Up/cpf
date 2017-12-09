//////////////////////////////////////////////////////////////////////////
#include "IO/FileStream.hpp"
#include <cstdio>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace IO
	{
		namespace FileStream
		{
			class RawFileStream : tRefCounted<Stream>
			{
			public:
				virtual Access GetAccess() override;
				virtual bool CanSeek() override;
				virtual bool CanRead() override;
				virtual bool CanWrite() override;
				virtual bool CanTimeout() override;

				//
				virtual void Close(Error* error = nullptr) override;
				virtual void Flush(Error* error = nullptr) override;
				virtual int64_t GetPosition(Error* error = nullptr) override;
				virtual int64_t GetLength(Error* error = nullptr) override;
				virtual void Seek(int64_t offset, StreamOrigin origin, Error* error = nullptr) override;

				//
				virtual int64_t Read(void* outBuffer, int32_t length, Error* error = nullptr) override;
				virtual int64_t Write(const void* inBuffer, int64_t length, Error* error = nullptr) override;

				//
				virtual void CopyTo(StreamPtr target, Error* error = nullptr) const override;

				//
				virtual operator bool() const override;

				//////////////////////////////////////////////////////////////////////////
				void Open(const Cpf::String& name, StreamAccess access)
				{
					char mode[4];
					switch (access)
					{
					case StreamAccess::eRead:
						strcpy(mode, "rb");
						break;
					case StreamAccess::eWrite:
						strcpy(mode, "wb");
						break;
					case StreamAccess::eBoth:
						strcpy(mode, "rb+");
						break;
					}
					mpFile = fopen(name.c_str(), mode);
				}

			private:
				FILE* mpFile;
			};

			/**
			 * @brief Creates a new file stream.
			 * @return A StreamPtr.
			 */
			StreamPtr Create(const Cpf::String& name, StreamAccess access)
			{
				RawFileStream* filestream = new RawFileStream;
				filestream->Open(name, access);
				return StreamPtr(reinterpret_cast<Stream*>(filestream));
			}


			//////////////////////////////////////////////////////////////////////////
			Stream::Access RawFileStream::GetAccess()
			{
				return StreamAccess::eBoth;
			}


			bool RawFileStream::CanSeek()
			{
				return true;
			}


			bool RawFileStream::CanRead()
			{
				return true;
			}


			bool RawFileStream::CanWrite()
			{
				return true;
			}


			bool RawFileStream::CanTimeout()
			{
				return false;
			}


			void RawFileStream::Close(Error* error)
			{
				auto res = fclose(mpFile);
				if (error)
					*error = res == 0 ? Error::eNone : Error::eGenericError;
			}

			void RawFileStream::Flush(Error* error)
			{
				auto res = fflush(mpFile);
				if (error)
					*error = res == 0 ? Error::eNone : Error::eGenericError;
			}

			int64_t RawFileStream::GetPosition(Error* error)
			{
				fpos_t pos;
				auto res = fgetpos(mpFile, &pos);
				if (error)
					*error = res == 0 ? Error::eNone : Error::eGenericError;
				return pos;
			}

			int64_t RawFileStream::GetLength(Error* error)
			{
				int64_t len = 0;
				if (mpFile)
				{
					auto origin = ftell(mpFile);
					fseek(mpFile, 0, SEEK_END);

					len = ftell(mpFile);
					fseek(mpFile, origin, SEEK_SET);

					if (error)
						*error = Error::eNone;
				}
				else
					if (error)
					*error = Error::eGenericError;

				return len;
			}

			void RawFileStream::Seek(int64_t offset, StreamOrigin origin, Error* error)
			{
				auto err = fseek(mpFile, long(offset), (origin == Origin::eBegin) ? SEEK_SET : ((origin == Origin::eCurrent) ? SEEK_CUR : SEEK_END));
				if (error)
					*error = err == 0 ? Error::eNone : Error::eGenericError;
			}

			int64_t RawFileStream::Read(void* outBuffer, int32_t length, Error* error)
			{
				int64_t len = fread(outBuffer, 1, length, mpFile);
				if (error)
					*error = len < 0 ? Error::eNone : ferror(mpFile) == 0 ? Error::eNone : Error::eGenericError;
				return len;
			}

			int64_t RawFileStream::Write(const void* inBuffer, int64_t length, Error* error)
			{
				int64_t len = fwrite(inBuffer, 1, length, mpFile);
				if (error)
					*error = len < length ? Error::eNone : ferror(mpFile) == 0 ? Error::eNone : Error::eGenericError;
				return len;
			}


			void RawFileStream::CopyTo(StreamPtr target, Error*) const
			{
				// Not implemented.
				CPF_ASSERT_ALWAYS;
			}


			RawFileStream::operator bool() const
			{
				return mpFile && ferror(mpFile) == 0;
			}
		}
	}
}

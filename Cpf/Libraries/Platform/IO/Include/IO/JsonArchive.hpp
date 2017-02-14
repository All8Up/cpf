//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/Archive.hpp"
#include "IO/Stream.hpp"
#include "IO/TextWriter.hpp"

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class JsonArchive : public Archive
			{
			public:
				JsonArchive(Stream* stream, int version) : mpStream(stream), mVersion(version) { if (mpStream) mpStream->AddRef(); }

			private:
				Stream* mpStream;
				int mVersion;
			};
		}
	}
}

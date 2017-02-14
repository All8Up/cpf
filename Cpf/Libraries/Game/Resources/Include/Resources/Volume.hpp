//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "RefCounted.hpp"
#include "String.hpp"

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class Stream;
		}
	}

	namespace Resources
	{
		struct ID;

		//////////////////////////////////////////////////////////////////////////
		class Volume : public iRefCounted
		{
		public:
			virtual bool Mount(const char* const) = 0;
			virtual void Unmount() = 0;

			virtual Platform::IO::Stream* Open(ID) = 0;

			struct Descriptor {};

		private:
		};
	}
}

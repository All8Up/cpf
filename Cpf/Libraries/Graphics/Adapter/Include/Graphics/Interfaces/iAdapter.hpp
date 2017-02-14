//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "iOutput.hpp"

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		class iAdapter : public iRefCounted
		{
		public:
			virtual ~iAdapter() = 0;

			virtual const char* GetDescription() const = 0;
			virtual size_t GetVideoMemory() const = 0;
			virtual size_t GetSystemMemory() const = 0;
			virtual size_t GetSharedMemory() const = 0;
			virtual bool IsSoftware() const = 0;
			virtual bool IsRemote() const = 0;

			virtual bool EnumerateOutputs(int32_t& count, iOutput**) const = 0;
		};
	}
}

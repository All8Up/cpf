//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iPython.hpp"

namespace CPF
{
	namespace Tools
	{
		class Python3 : public tRefCounted<iPython3>
		{
		public:
			Python3(iUnknown*);
			virtual ~Python3();

			// iBase overrides.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// iPython3 overrides.
			GOM::Result CPF_STDCALL Initialize(const char* basePath, CreateRegistryPtr) override;
			GOM::Result CPF_STDCALL Shutdown() override;

			// Internal interface.
			GOM::Result CreateRegistry(Plugin::iRegistry**) const;

		private:
			bool _InitPython();

			CreateRegistryPtr mpCreateRegistry;
		};
	}
}

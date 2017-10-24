//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin/iRegistry.hpp"
#include "Plugin/tClassInstance.hpp"
#include "CPF/IO/Detail/DefaultFile.hpp"

namespace CPF
{
	namespace IO
	{
		class DefaultIO
		{
		public:
			static GOM::Result Install(Plugin::iRegistry* regy)
			{
				if (GOM::Succeeded(regy->Install(kDefaultFileCID.GetID(), new Plugin::tClassInstance<DefaultFile>())))
				{
					iFile* fileInstance = nullptr;
					if (GOM::Succeeded(regy->Create(nullptr, kDefaultFileCID.GetID(), iFile::kIID.GetID(), (void**)&fileInstance)))
					{
						if (GOM::Succeeded(regy->InstanceInstall(iFile::kIID.GetID(), fileInstance)))
						{
							return GOM::kOK;
						}
					}
				}
				return GOM::kError;
			}
		};
	}
}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin/iRegistry.hpp"
#include "Plugin/tClassInstance.hpp"
#include "CPF/IO/Detail/DefaultDirectory.hpp"
#include "CPF/IO/Detail/DefaultExecutor.hpp"
#include "CPF/IO/Detail/DefaultFile.hpp"
#include "CPF/IO/Detail/DefaultFileStream.hpp"

namespace CPF
{
	namespace IO
	{
		class DefaultIO
		{
		public:
			static GOM::Result Install(Plugin::iRegistry* regy)
			{
				// Create and install an execution environment.
				if (GOM::Succeeded(regy->Install(kDefaultExecutorCID.GetID(), new Plugin::tClassInstance<DefaultExecutor>())))
				{
					GOM::Result errorResult;
					iExecutor* executorInstance = nullptr;
					if (GOM::Succeeded(errorResult = regy->Create(nullptr, kDefaultExecutorCID.GetID(), iExecutor::kIID.GetID(), (void**)&executorInstance)))
					{
						if (GOM::Succeeded(errorResult = regy->InstanceInstall(iExecutor::kIID.GetID(), executorInstance)))
						{
							//////////////////////////////////////////////////////////////////////////
							// Now install the instances.
							if (GOM::Succeeded(regy->Install(kDefaultFileCID.GetID(), new Plugin::tClassInstance<DefaultFile>())) &&
								GOM::Succeeded(regy->Install(kDefaultFileStreamCID.GetID(), new Plugin::tClassInstance<DefaultFileStream>())))
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
						}
					}
					return errorResult;
				}
				return GOM::kError;
			}
		};
	}
}

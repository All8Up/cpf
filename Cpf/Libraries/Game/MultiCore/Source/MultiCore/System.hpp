//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "MultiCore/Export.hpp"
#include "MultiCore/Types.hpp"
#include "Plugin/iRegistry.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "MultiCore/iSystem.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class StageList : public tRefCounted<iStageList>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override
			{
				if (outIface)
				{
					switch (id.GetID())
					{
					case COM::iUnknown::kIID.GetID():
						*outIface = static_cast<COM::iUnknown*>(this);
						break;

					case iStageList::kIID.GetID():
						*outIface = static_cast<iStageList*>(this);
						break;

					default:
						*outIface = nullptr;
						return COM::kUnknownInterface;
					}
					AddRef();
					return COM::kOK;
				}
				return COM::kUnknownInterface;
			}

			COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			COM::Result CPF_STDCALL AddStage(iStage* stage) override;
			COM::Result CPF_STDCALL RemoveStage(StageID id) override;

		private:
			StageVector mStages;
		};

		class StageListClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new StageList;
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}

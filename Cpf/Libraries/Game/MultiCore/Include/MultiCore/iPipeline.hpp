//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		struct iSystem;

		static constexpr COM::ClassID kPipelineCID = COM::ClassID("Pipeline"_crc64);
		struct iPipeline : COM::iUnknown
		{
			static constexpr COM::InterfaceID kID = COM::InterfaceID("iPipeline"_crc64);
			static constexpr COM::Result kConfigurationError = COM::CreateResult(1, 50, 1);

			virtual iSystem* CPF_STDCALL Install(iSystem*) = 0;
			virtual COM::Result CPF_STDCALL Remove(iSystem*) = 0;
			virtual COM::Result CPF_STDCALL Configure() = 0;
			virtual COM::Result CPF_STDCALL GetSystem(SystemID, iSystem**) const = 0;
			virtual COM::Result CPF_STDCALL GetSystem(const char* const, iSystem**) const = 0;
			virtual COM::Result CPF_STDCALL GetStage(SystemID, StageID, Stage**) = 0;
			virtual void CPF_STDCALL Submit(Concurrency::Scheduler*) = 0;
			virtual COM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) = 0;
			virtual COM::Result CPF_STDCALL GetSystems(int32_t* count, iSystem**) = 0;
		};

		template <typename TYPE>
		TYPE* GetSystem(iPipeline* pipeline, const String& name)
		{
			iSystem* result = nullptr;
			if (COM::Succeeded(pipeline->GetSystem(name.c_str(), &result)))
				return static_cast<TYPE*>(result);
			return nullptr;
		}
	}
}

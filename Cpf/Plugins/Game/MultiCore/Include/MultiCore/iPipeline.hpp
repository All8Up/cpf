//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "GOM/iBase.hpp"
#include "Plugin/iRegistry.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		struct iSystem;

		static constexpr GOM::ClassID kPipelineCID = GOM::ClassID("Pipeline"_crc64);

		/**
		 A multicore pipeline execution component.
		 */
		struct iPipeline : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iPipeline"_crc64);
			static constexpr GOM::Result kConfigurationError = GOM::CreateResult(1, 50, 1);

			virtual iSystem* CPF_STDCALL Install(iSystem*) = 0;
			virtual GOM::Result CPF_STDCALL Remove(iSystem*) = 0;
			virtual GOM::Result CPF_STDCALL Configure(Plugin::iRegistry* regy) = 0;
			virtual GOM::Result CPF_STDCALL GetSystem(SystemID, iSystem**) const = 0;
			virtual GOM::Result CPF_STDCALL GetSystem(const char* const, iSystem**) const = 0;
			virtual GOM::Result CPF_STDCALL GetStage(SystemID, StageID, iStage**) = 0;
			virtual void CPF_STDCALL Submit(Concurrency::iScheduler*) = 0;
			virtual GOM::Result CPF_STDCALL GetQueueInfo(int32_t idx, const char**) = 0;
			virtual GOM::Result CPF_STDCALL GetSystems(int32_t* count, iSystem**) = 0;
		};

		/**
		 Helper to get a system by name from the given pipeline.
		 @tparam TYPE Type of the system.
		 @param [in,out] pipeline The pipeline that contains the system.
		 @param name The name of the system to get.
		 @return Null if it fails, else the system.
		 */
		template <typename TYPE>
		TYPE* GetSystem(iPipeline* pipeline, const String& name)
		{
			iSystem* result = nullptr;
			if (GOM::Succeeded(pipeline->GetSystem(name.c_str(), &result)))
				return static_cast<TYPE*>(result);
			return nullptr;
		}
	}
}

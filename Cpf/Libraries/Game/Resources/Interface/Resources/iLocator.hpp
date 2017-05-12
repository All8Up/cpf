//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Events/Event.hpp"
#include "IO/Stream.hpp"

namespace Cpf
{
	namespace Resources
	{
		static constexpr COM::ClassID kLocatorCID = COM::ClassID("Cpf::Resources::iLocator"_crc64);

		//////////////////////////////////////////////////////////////////////////
		struct ID;
		struct iCache;
		struct iMonitor;
		struct iVolume;

		struct iLoader;
		struct iResource;

		struct LoaderInfo
		{
			iLoader* mpLoader;
			iCache* mpCache;
		};

		//////////////////////////////////////////////////////////////////////////
		struct iLocator : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::Resources::iLocator"_crc64);

			//////////////////////////////////////////////////////////////////////////
			using Mounted = Events::Event<0, Function<void(const char* const, iVolume*)>>;
			using Unmounted = Events::Event<1, Function<void(const char* const, iVolume*)>>;

			virtual Events::Emitter& CPF_STDCALL GetEmitter() = 0;

			//////////////////////////////////////////////////////////////////////////
			virtual bool CPF_STDCALL Mount(const char* const, iVolume*) = 0;
			virtual bool CPF_STDCALL Unmount(iVolume*) = 0;

			virtual bool CPF_STDCALL Attach(const char* const, iCache*) = 0;
			virtual bool CPF_STDCALL Detach(const char* const) = 0;
			virtual iCache* CPF_STDCALL GetCache(const char* const) const = 0;

			virtual bool CPF_STDCALL Attach(iMonitor*) = 0;
			virtual bool CPF_STDCALL Detach(iMonitor*) = 0;

			virtual bool CPF_STDCALL Install(iLoader*, iCache*) = 0;
			virtual bool CPF_STDCALL Remove(iLoader*) = 0;
			virtual const LoaderInfo* CPF_STDCALL GetLoader(uint32_t id) const = 0;

			virtual Platform::IO::Stream* CPF_STDCALL Open(ID) const = 0;
			virtual iResource* CPF_STDCALL GetResource(ID) const = 0;

			virtual bool CPF_STDCALL Touch(ID) = 0;
			virtual void CPF_STDCALL TouchAll() = 0;

			template<typename TYPE>
			typename TYPE::Resource* Load(ID);
		};

		template<typename TYPE>
		typename TYPE::Resource* iLocator::Load(ID id)
		{
			auto info = GetLoader(TYPE::kID);
			if (info != nullptr)
			{
				return static_cast<typename TYPE::Resource*>((*static_cast<TYPE*>(info->mpLoader))(id));
			}
			return nullptr;
		}
	}
}

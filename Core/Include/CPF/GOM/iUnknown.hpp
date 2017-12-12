//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/GOM/Types.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/IntrusivePtr.hpp"

namespace CPF
{
	namespace GOM
	{
		//////////////////////////////////////////////////////////////////////////
		struct iUnknown
		{
			static constexpr InterfaceID kIID = InterfaceID("Cpf::GOM::iUnknown"_crc64);

			virtual int32_t CPF_STDCALL AddRef() = 0;
			virtual int32_t CPF_STDCALL Release() = 0;
			virtual Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		// Utility helper to implement iUnknown objects.
		template<typename IFACE>
		class tUnknown : public IFACE
		{
		public:
			tUnknown();

			virtual ~tUnknown() {}

			virtual int32_t CPF_STDCALL AddRef() override;
			virtual int32_t CPF_STDCALL Release() override;
			virtual Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		private:
			int32_t mRefCount;
		};

		//////////////////////////////////////////////////////////////////////////
		template<typename IFACE>
		tUnknown<IFACE>::tUnknown()
			: mRefCount(1)
		{}

		template<typename IFACE>
		int32_t CPF_STDCALL tUnknown<IFACE>::AddRef()
		{
			CPF_ASSERT(mRefCount > 0);
			return ++mRefCount;
		}

		template<typename IFACE>
		int32_t CPF_STDCALL tUnknown<IFACE>::Release()
		{
			CPF_ASSERT(mRefCount > 0);
			if (--mRefCount == 0)
			{
				delete this;
				return 0;
			}
			return mRefCount;
		}

		template<typename IFACE>
		Result CPF_STDCALL tUnknown<IFACE>::QueryInterface(uint64_t id, void** outIface)
		{
			if (outIface)
			{
				switch (id)
				{
				case iUnknown::kIID.GetID():
					*outIface = static_cast<iUnknown*>(this);
					break;
				case IFACE::kIID.GetID():
					*outIface = static_cast<IFACE*>(this);
					break;
				default:
					return kUnknownInterface;
				}
				AddRef();
				return kOK;
			}
			return kInvalidParameter;
		}
	}
}

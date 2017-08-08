//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "GOM/Result.hpp"

namespace Cpf
{
	namespace GOM
	{
		struct class_tag;
		using ClassID = Hash::HashID<uint64_t, class_tag>;
		struct interface_tag;
		using InterfaceID = Hash::HashID<uint64_t, interface_tag>;
		struct instance_tag;
		using InstanceID = Hash::HashID<uint64_t, instance_tag>;

		static_assert(sizeof(ClassID) == sizeof(uint64_t), "Size is incorrect.");
		static_assert(sizeof(InterfaceID) == sizeof(uint64_t), "Size is incorrect.");

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

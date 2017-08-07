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
		template<typename BASE = iUnknown>
		class tUnknown : public BASE
		{
		public:
			template<typename... PARAMS>
			tUnknown(PARAMS... params);
			tUnknown();

			virtual ~tUnknown() {}

			virtual int32_t CPF_STDCALL AddRef() override;
			virtual int32_t CPF_STDCALL Release() override;
			virtual Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		private:
			int32_t mRefCount;
		};

		//////////////////////////////////////////////////////////////////////////
		template<typename BASE>
		template<typename... PARAMS> inline
			tUnknown<BASE>::tUnknown(PARAMS... params)
			: BASE(params...)
			, mRefCount(1)
		{}

		template<typename BASE> inline
			tUnknown<BASE>::tUnknown()
			: mRefCount(1)
		{}

		template<typename BASE> inline
			int32_t CPF_STDCALL tUnknown<BASE>::AddRef()
		{
			CPF_ASSERT(mRefCount > 0);
			return ++mRefCount;
		}

		template<typename BASE> inline
			int32_t CPF_STDCALL tUnknown<BASE>::Release()
		{
			CPF_ASSERT(mRefCount > 0);
			if (--mRefCount == 0)
			{
				delete this;
				return 0;
			}
			return mRefCount;
		}

		template<typename BASE> inline
			Result CPF_STDCALL tUnknown<BASE>::QueryInterface(uint64_t id, void** outIface)
		{
			(void)id; (void)outIface;
			return kNotImplemented;
		}
	}
}

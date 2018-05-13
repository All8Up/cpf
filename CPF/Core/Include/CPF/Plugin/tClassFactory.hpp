//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin/iClassFactory.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Plugin
	{
		/**
		* @brief A helper to create class factories.
		* @tparam TYPE Type of instance to create.
		*/
		template <typename TYPE>
		class tClassFactory : public GOM::tUnknown<iClassFactory>
		{
		public:
			tClassFactory() = default;
			tClassFactory(const char* name, SemVer version = SemVer{0, 0, 0});
			tClassFactory(const char* name, const char* desc, SemVer version = SemVer{ 0, 0, 0 });
			tClassFactory(tClassFactory&&) = delete;
			tClassFactory(const tClassFactory&) = delete;
			virtual ~tClassFactory() = default;

			tClassFactory& operator = (tClassFactory&&) = delete;
			tClassFactory& operator = (const tClassFactory&) = delete;

			GOM::Result CPF_STDCALL CreateInstance(iRegistry* regy, iUnknown* outer, iUnknown** outIface) override;
			GOM::Result CPF_STDCALL GetName(int32_t* charCount, char* outName) override;
			GOM::Result CPF_STDCALL GetDescription(int32_t* charCount, char* outDesc) override;
			GOM::Result CPF_STDCALL GetVersion(SemVer* outVersion) override;

		private:
			/**
			@brief Determine which constructor signature is available.
			@tparam TYPE Type of the class being constructed.
			*/
			struct ClassConstructorType
			{
				static constexpr int Variant =
					std::is_constructible<TYPE>::value ? 1 : 0 |
					std::is_constructible<TYPE, iRegistry*>::value ? 2 : 0 |
					std::is_constructible<TYPE, iRegistry*, iUnknown*>::value ? 4 : 0 |
					std::is_constructible<TYPE, iUnknown*>::value ? 8 : 0;
			};

			template <typename TARGET, int VARIANT>
			struct InstanceCreator;

			template <typename TARGET>
			struct InstanceCreator<TARGET, 1> { static GOM::Result Create(iRegistry*, iUnknown*, iUnknown** outIface); };
			template <typename TARGET>
			struct InstanceCreator<TARGET, 2> { static GOM::Result Create(iRegistry* regy, iUnknown*, iUnknown** outIface); };
			template <typename TARGET>
			struct InstanceCreator<TARGET, 4> { static GOM::Result Create(iRegistry* regy, iUnknown* outer, iUnknown** outIface); };
			template <typename TARGET>
			struct InstanceCreator<TARGET, 8> { static GOM::Result Create(iRegistry*, iUnknown* outer, iUnknown** outIface); };

			STD::String mName;
			STD::String mDescription;
			SemVer mVersion;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		tClassFactory<TYPE>::tClassFactory(const char* name, SemVer version)
			: mName(name)
			, mVersion(version)
		{}

		template <typename TYPE>
		tClassFactory<TYPE>::tClassFactory(const char* name, const char* desc, SemVer version)
			: mName(name)
			, mDescription(desc)
			, mVersion(version)
		{}

		template <typename TYPE>
		GOM::Result CPF_STDCALL tClassFactory<TYPE>::CreateInstance(iRegistry* regy, iUnknown* outer, iUnknown** outIface)
		{
			if (outIface)
			{
				return InstanceCreator<TYPE, ClassConstructorType::Variant>::Create(regy, outer, outIface);
			}
			return GOM::kInvalidParameter;
		}

		template <typename TYPE>
		GOM::Result CPF_STDCALL tClassFactory<TYPE>::GetName(int32_t* charCount, char* outName)
		{
			(void)charCount;
			(void)outName;
			return GOM::kNotImplemented;
		}

		template <typename TYPE>
		GOM::Result CPF_STDCALL tClassFactory<TYPE>::GetDescription(int32_t* charCount, char* outDesc)
		{
			(void)charCount;
			(void)outDesc;
			return GOM::kNotImplemented;
		}

		template <typename TYPE>
		GOM::Result CPF_STDCALL tClassFactory<TYPE>::GetVersion(SemVer* outVersion)
		{
			(void)outVersion;
			return GOM::kNotImplemented;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		template <typename TARGET>
		GOM::Result tClassFactory<TYPE>::InstanceCreator<TARGET, 1>::Create(iRegistry*, iUnknown*, iUnknown** outIface)
		{
			*outIface = new TARGET();
			if (*outIface)
				return GOM::kOK;
			return GOM::kOutOfMemory;
		}

		template <typename TYPE>
		template <typename TARGET>
		GOM::Result tClassFactory<TYPE>::InstanceCreator<TARGET, 2>::Create(iRegistry* regy, iUnknown*, iUnknown** outIface)
		{
			*outIface = new TARGET(regy);
			if (*outIface)
				return GOM::kOK;
			return GOM::kOutOfMemory;
		}

		template <typename TYPE>
		template <typename TARGET>
		GOM::Result tClassFactory<TYPE>::InstanceCreator<TARGET, 4>::Create(iRegistry* regy, iUnknown* outer, iUnknown** outIface)
		{
			*outIface = new TARGET(regy, outer);
			if (*outIface)
				return GOM::kOK;
			return GOM::kOutOfMemory;
		}

		template <typename TYPE>
		template <typename TARGET>
		GOM::Result tClassFactory<TYPE>::InstanceCreator<TARGET, 8>::Create(iRegistry*, iUnknown*, iUnknown** outIface)
		{
			*outIface = new TARGET();
			if (*outIface)
				return GOM::kOK;
			return GOM::kOutOfMemory;
		}
	}
}

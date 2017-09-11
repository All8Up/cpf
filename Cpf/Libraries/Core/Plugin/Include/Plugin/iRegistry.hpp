//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct IID_CID;
		struct iClassInstance;

		static constexpr GOM::Result kInstanceExists = GOM::CreateResult(1, "Plugin"_crc15, "Instance already exists"_crc16);
		static constexpr GOM::Result kNotInstalled = GOM::CreateResult(1, "Plugin"_crc15, "Instance not installed"_crc16);
		static constexpr GOM::Result kNotLoaded = GOM::CreateResult(1, "Plugin"_crc15, "Plugin not loaded"_crc16);
		static constexpr GOM::Result kCantUnload = GOM::CreateResult(1, "Plugin"_crc15, "Plugin can not be unloaded"_crc16);
		static constexpr GOM::Result kExportMissing = GOM::CreateResult(1, "Plugin"_crc15, "Plugin does not expose correct function"_crc16);

		/**
		 Class instance registry.
		 */
		struct iRegistry : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::Plugin::iRegistry"_crc64);

			/**
			 * @brief Attempts to load a library as a plugin.
			 * @param library The library to load.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Load(const char* library) = 0;

			/**
			 * @brief Unloads the given library.
			 * @param library The library to unload.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Unload(const char* library) = 0;

			/**
			 * @brief Installs a class instance.
			 * @param cid The class instance id.
			 * @param [in,out] clsInst The class instance object.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Install(uint64_t cid, iClassInstance* clsInst) = 0;

			/**
			 * @brief Removes a class instance.
			 * @param cid The instance id.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Remove(uint64_t cid) = 0;

			/**
			 @brief Gets the class instance associated with the cid.
			 @param cid The cid of interest.
			 @param clsInst Pointer to the resulting interface pointer.
			 @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL GetClassInstance(uint64_t cid, iClassInstance** clsInst) = 0;

			/**
			 * @brief Check if a class id has a class instance installed.
			 * @param cid The class instance id.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Exists(uint64_t cid) = 0;

			/**
			 * @brief Creates an instance.
			 * @param [in,out] outer Aggregation outer object or null.
			 * @param cid The class instance id to create.
			 * @param iid The interface id to store in the result.
			 * @param [out] result Various error codes or GOM::kOK.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL Create(iUnknown* outer, uint64_t cid, uint64_t iid, void** result) = 0;

			/**
			 * @brief Install a set of class id's and instance id's.
			 * @param count The number of pairs in the array.
			 * @param pairs The interface id and the class id's which implement them.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL ClassInstall(int32_t count, const IID_CID* pairs) = 0;

			/**
			 * @brief Remove a set of class id's and instance id's.
			 * @param count The number of pairs in the array.
			 * @param pairs The interface id and the class id pairs to remove.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL ClassRemove(int32_t count, const IID_CID* pairs) = 0;

			/**
			 * @brief Looks up class id's which implement a specific interface id.
			 * @param id The interface id to look up.
			 * @param [in,out] count A count variable to retried the number of class id's or the size of the cid array.
			 * @param [in,out] cid The output array of class id's.
			 * @return A result code.
			 */
			virtual GOM::Result CPF_STDCALL GetClasses(uint64_t id, int32_t* count, uint64_t* cid) = 0;

			/**
			 * @brief Install an instance for the given interface id.
			 * @param id The interface id for the singleton.
			 * @param [in,out] instance If non-null, the instance pointer to install.
			 * @return A GOM::Result, kOK if all is ok.
			 */
			virtual GOM::Result CPF_STDCALL InstanceInstall(uint64_t id, iUnknown* instance) = 0;

			/**
			 * @brief Remove an instance from the instances.
			 * @param id The interface id for the singleton.
			 * @return A GOM::Result, kOK if the instance was removed.
			 */
			virtual GOM::Result CPF_STDCALL InstanceRemove(uint64_t id) = 0;

			/**
			 * @brief Get the instance for the given interface.
			 * @param id The interface id for the singleton.
			 * @param [in,out] outIface If non-null, the output.
			 * @return The GOM::Result, kOK if the instance was found and put in the output.
			 */
			virtual GOM::Result CPF_STDCALL GetInstance(uint64_t id, iUnknown** outIface) = 0;
		};
	}
}

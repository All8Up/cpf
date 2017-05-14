//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct IID_CID;
		struct iClassInstance;

		static constexpr COM::Result kInstanceExists = COM::CreateResult(1, "Plugin"_crc16, "Instance already exists"_crc16);
		static constexpr COM::Result kNotInstalled = COM::CreateResult(1, "Plugin"_crc16, "Instance not installed"_crc16);

		/**
		 Class instance registry.
		 */
		struct iRegistry : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iRegistry"_crc64);

			/**
			 * @brief Attempts to load a library as a plugin.
			 * @param library The library to load.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL Load(const char* const library) = 0;

			/**
			 * @brief Installs a class instance.
			 * @param cid The class instance id.
			 * @param [in,out] clsInst The class instance object.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL Install(COM::ClassID cid, iClassInstance* clsInst) = 0;

			/**
			 * @brief Removes a class instance.
			 * @param cid The instance id.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL Remove(COM::ClassID cid) = 0;

			/**
			 * @brief Check if a class id has a class instance installed.
			 * @param cid The class instance id.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL Exists(COM::ClassID cid) = 0;

			/**
			 * @brief Creates an instance.
			 * @param [in,out] outer Aggregation outer object or null.
			 * @param cid The class instance id to create.
			 * @param iid The interface id to store in the result.
			 * @param [out] result Various error codes or COM::kOK.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL Create(COM::iUnknown* outer, COM::ClassID cid, COM::InterfaceID iid, void** result) = 0;

			/**
			 * @brief Install a set of class id's and instance id's.
			 * @param count The number of pairs in the array.
			 * @param pairs The interface id and the class id's which implement them.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL ClassInstall(int32_t count, const IID_CID* pairs) = 0;

			/**
			 * @brief Remove a set of class id's and instance id's.
			 * @param count The number of pairs in the array.
			 * @param pairs The interface id and the class id pairs to remove.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL ClassRemove(int32_t count, const IID_CID* pairs) = 0;

			/**
			 * @brief Looks up class id's which implement a specific interface id.
			 * @param id The interface id to look up.
			 * @param [in,out] count A count variable to retried the number of class id's or the size of the cid array.
			 * @param [in,out] cid The output array of class id's.
			 * @return A result code.
			 */
			virtual COM::Result CPF_STDCALL GetClasses(COM::InterfaceID id, int32_t* count, COM::ClassID* cid) = 0;

			/**
			 * @brief Install an instance for the given interface id.
			 * @param id The interface id for the singleton.
			 * @param [in,out] instance If non-null, the instance pointer to install.
			 * @return A COM::Result, kOK if all is ok.
			 */
			virtual COM::Result CPF_STDCALL InstanceInstall(COM::InterfaceID id, void* instance) = 0;

			/**
			 * @brief Remove an instance from the instances.
			 * @param id The interface id for the singleton.
			 * @return A COM::Result, kOK if the instance was removed.
			 */
			virtual COM::Result CPF_STDCALL InstanceRemove(COM::InterfaceID id) = 0;

			/**
			 * @brief Get the instance for the given interface.
			 * @param id The interface id for the singleton.
			 * @param [in,out] outIface If non-null, the output.
			 * @return The COM::Result, kOK if the instance was found and put in the output.
			 */
			virtual COM::Result CPF_STDCALL GetInstance(COM::InterfaceID id, void** outIface) = 0;
		};
	}
}

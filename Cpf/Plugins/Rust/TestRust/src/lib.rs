#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use libc::{c_char};

pub mod CPF
{
    pub mod GOM
    {
        pub const OK                               : u32 = 0x72D622E4;      // Sub-system: "Core" Code: "OK"
        pub const IN_USE                           : u32 = 0x72D65159;      // Sub-system: "Core" Code: "InUse"
        pub const ERROR                            : u32 = 0xF2D60ECC;      // Sub-system: "Core" Code: "Error"
        pub const UNKNOWN_INTERFACE                : u32 = 0xF2D623E7;      // Sub-system: "Core" Code: "UnknownInterface"
        pub const INVALID_PARAMETER                : u32 = 0xF2D60CEA;      // Sub-system: "Core" Code: "InvalidParameter"
        pub const OUT_OF_MEMORY                    : u32 = 0xF2D655B8;      // Sub-system: "Core" Code: "OutOfMemory"
        pub const UNKNOWN_CLASS                    : u32 = 0xF2D67F71;      // Sub-system: "Core" Code: "UnknownClass"
        pub const NOT_IMPLEMENTED                  : u32 = 0xF2D67EFE;      // Sub-system: "Core" Code: "NotImplemented"
        pub const INVALID                          : u32 = 0xF2D63EDB;      // Sub-system: "Core" Code: "Invalid"
        pub const NOT_ENOUGH_SPACE                 : u32 = 0xF2D6075E;      // Sub-system: "Core" Code: "NotEnoughSpace"
        pub const NOT_INITIALIZED                  : u32 = 0xF2D66D72;      // Sub-system: "Core" Code: "NotInitialized"
        pub const INITIALIZATION_FAILURE           : u32 = 0xF2D66346;      // Sub-system: "Core" Code: "InitializationFailure"
        pub const OUT_OF_RANGE                     : u32 = 0xF2D6436A;      // Sub-system: "Core" Code: "OutOfRange"
        pub const DUPLICATE                        : u32 = 0xF2D675B4;      // Sub-system: "Core" Code: "Duplicate"
        pub const REGISTRY_ERROR                   : u32 = 0xF2D62784;      // Sub-system: "Core" Code: "RegistryError"
        pub const NOT_RUNNING                      : u32 = 0xF2D67C4C;      // Sub-system: "Core" Code: "NotRunning"

        pub struct iBase_Vtbl
        {
            AddRef: extern fn() -> u32,
            Release: extern fn() -> u32,
            Cast: extern fn(id: u64, outIface: ::libc::c_void) -> u32,
        }
        pub struct iBase
        {
        	vtbl: *const iBase_Vtbl
        }
        pub struct IID_CID
        {}
    }
    pub mod Plugin
    {

        pub struct iRegistry_Vtbl
        {
            Load: extern fn(library: ::libc::c_char) -> u32,
            CanUnload: extern fn(library: ::libc::c_char) -> u32,
            Unload: extern fn(library: ::libc::c_char) -> u32,
            Install: extern fn(cid: u64, clsInst: iClassInstance) -> u32,
            Remove: extern fn(cid: u64) -> u32,
            GetClassInstance: extern fn(cid: u64, clsInst: iClassInstance) -> u32,
            Exists: extern fn(cid: u64) -> u32,
            Create: extern fn(outer: ::CPF::GOM::iBase, cid: u64, iid: u64, outIFace: ::libc::c_void) -> u32,
            ClassInstall: extern fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            ClassRemove: extern fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            GetClasses: extern fn(id: u64, count: i32, cid: u64) -> u32,
            InstanceInstall: extern fn(id: u64, instance: ::CPF::GOM::iBase) -> u32,
            InstanceRemove: extern fn(id: u64) -> u32,
            GetInstance: extern fn(id: u64, outIface: ::CPF::GOM::iBase) -> u32,
        }
        pub struct iRegistry
        {
        	vtbl: *const iRegistry_Vtbl
        }

        pub struct iClassInstance_Vtbl
        {
            CreateInstance: extern fn(registry: iRegistry, outer: ::CPF::GOM::iBase, outIface: ::CPF::GOM::iBase) -> u32,
        }
        pub struct iClassInstance
        {
        	vtbl: *const iClassInstance_Vtbl
        }
    }
}


#[no_mangle]
pub extern "stdcall" fn Install(registry: *const ::CPF::Plugin::iRegistry) -> u32
{
	CPF::GOM::OK
}

#[no_mangle]
pub extern "stdcall" fn CanUnload() -> u32
{
	CPF::GOM::OK
}

#[no_mangle]
pub extern "stdcall" fn Remove(registry: *const ::CPF::Plugin::iRegistry) -> u32
{
	CPF::GOM::OK
}

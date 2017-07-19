#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;

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
            pub AddRef: extern "stdcall" fn() -> u32,
            pub Release: extern "stdcall" fn() -> u32,
            pub Cast: extern "stdcall" fn(id: u64, outIface: ::libc::c_void) -> u32,
        }
        pub struct iBase
        {
        	pub vtbl: *const iBase_Vtbl
        }
        pub struct IID_CID
        {}
    }
    pub mod Plugin
    {

        pub struct iRegistry_Vtbl
        {
            pub Load: extern "stdcall" fn(library: ::libc::c_char) -> u32,
            pub CanUnload: extern "stdcall" fn(library: ::libc::c_char) -> u32,
            pub Unload: extern "stdcall" fn(library: ::libc::c_char) -> u32,
            pub Install: extern "stdcall" fn(cid: u64, clsInst: iClassInstance) -> u32,
            pub Remove: extern "stdcall" fn(cid: u64) -> u32,
            pub GetClassInstance: extern "stdcall" fn(cid: u64, clsInst: iClassInstance) -> u32,
            pub Exists: extern "stdcall" fn(cid: u64) -> u32,
            pub Create: extern "stdcall" fn(outer: ::CPF::GOM::iBase, cid: u64, iid: u64, outIFace: ::libc::c_void) -> u32,
            pub ClassInstall: extern "stdcall" fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            pub ClassRemove: extern "stdcall" fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            pub GetClasses: extern "stdcall" fn(id: u64, count: i32, cid: u64) -> u32,
            pub InstanceInstall: extern "stdcall" fn(id: u64, instance: ::CPF::GOM::iBase) -> u32,
            pub InstanceRemove: extern "stdcall" fn(id: u64) -> u32,
            pub GetInstance: extern "stdcall" fn(id: u64, outIface: ::CPF::GOM::iBase) -> u32,
        }
        pub struct iRegistry
        {
        	pub vtbl: *const iRegistry_Vtbl
        }

        pub struct iClassInstance_Vtbl
        {
            pub AddRef: extern "stdcall" fn(this: *mut iClassInstance) -> u32,
            pub Release: extern "stdcall" fn(this: *mut iClassInstance) -> u32,
            pub Cast: extern "stdcall" fn(this: *mut iClassInstance, id: u64, outIface: ::libc::c_void) -> u32,
            pub CreateInstance: extern "stdcall" fn(this: *mut iClassInstance, registry: iRegistry, outer: ::CPF::GOM::iBase, outIface: ::CPF::GOM::iBase) -> u32,
        }
        pub struct iClassInstance
        {
        	pub vtbl: *const iClassInstance_Vtbl
        }
    }
}


// *****************
struct TestRustCreator
{
    ref_count: u32
}

impl TestRustCreator
{
    pub fn add_ref(&mut self) -> u32
    {
        self.ref_count = self.ref_count + 1;
        return self.ref_count;
    }
    pub fn release(&mut self) -> u32
    {
        self.ref_count -= 1;
        return self.ref_count;
    }
    pub fn cast(&self, id: u64, out_iface: ::libc::c_void) -> u32
    {
        ::CPF::GOM::UNKNOWN_CLASS
    }
    pub fn create_instance(&self, registry: ::CPF::Plugin::iRegistry, outer: ::CPF::GOM::iBase, out_iface: ::CPF::GOM::iBase) -> u32
    {
        ::CPF::GOM::UNKNOWN_CLASS
    }
}

extern "stdcall" fn add_ref(this: *mut ::CPF::Plugin::iClassInstance) -> u32
{
    unsafe
    {
        let ref mut This: TestRustCreator = *(this as *mut TestRustCreator);
        This.add_ref()
    }
}
extern "stdcall" fn release(this: *mut ::CPF::Plugin::iClassInstance) -> u32
{
    unsafe
    {
        let ref mut This: TestRustCreator = *(this as *mut TestRustCreator);
        This.release()
    }
}
extern "stdcall" fn cast(
    this: *mut ::CPF::Plugin::iClassInstance,
    iid: u64,
    out_iface: ::libc::c_void) -> u32
{
    ::CPF::GOM::UNKNOWN_CLASS
}

extern "stdcall" fn test_create(
    this: *mut ::CPF::Plugin::iClassInstance,
    registry: ::CPF::Plugin::iRegistry,
    outer: ::CPF::GOM::iBase,
    outIface: ::CPF::GOM::iBase) -> u32
{
    CPF::GOM::OK
}

static sTestClassInstance: ::CPF::Plugin::iClassInstance_Vtbl = ::CPF::Plugin::iClassInstance_Vtbl
{
    AddRef: add_ref,
    Release: release,
    Cast: cast,
    CreateInstance: test_create
};

// **************************
#[no_mangle]
pub extern "stdcall" fn Install(registry: *const ::CPF::Plugin::iRegistry) -> u32
{

//    ((*(*registry).vtbl).Install)(0, sTestClassInstance);
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

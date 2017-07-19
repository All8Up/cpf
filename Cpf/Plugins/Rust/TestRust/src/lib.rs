#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]
mod cpf;
use cpf::*;
extern crate libc;

// *****************
struct iTestPlugin_Vtbl
{
    pub AddRef: extern "stdcall" fn(this: *mut iTestPlugin) -> i32,
    pub Release: extern "stdcall" fn(this: *mut iTestPlugin) -> i32,
    pub Cast: extern "stdcall" fn(this: *mut iTestPlugin, id: u64, outIface: *mut *mut ::libc::c_void) -> u32,
}
struct iTestPlugin
{
    vtbl: *const iTestPlugin_Vtbl,
    ref_count: i32
}

static TEST_PLUGIN_VTABLE: iTestPlugin_Vtbl = iTestPlugin_Vtbl
{
    AddRef: iTestPlugin_add_ref,
    Release: iTestPlugin_release,
    Cast: iTestPlugin_cast
};

extern "stdcall" fn iTestPlugin_add_ref(this: *mut iTestPlugin) -> i32
{
    unsafe
    {
        println!("Add ref'd the test rust plugin.");
        (*this).ref_count += 1;
        (*this).ref_count
    }
}
extern "stdcall" fn iTestPlugin_release(this: *mut iTestPlugin) -> i32
{
    unsafe
    {
        println!("Released the test rust plugin.");
        (*this).ref_count -= 1;
        if (*this).ref_count == 0
        {
            println!("And deleted the test rust plugin.");
            Box::from_raw(this);
            return 0;
        }
        (*this).ref_count
    }
}
extern "stdcall" fn iTestPlugin_cast(this: *mut iTestPlugin, iid: u64, out_iface: *mut *mut ::libc::c_void) -> u32
{
    unsafe
    {
        match iid
        {
            // TODO: Need a method to generate IID's in Rust code.
            // I would like to use a compiler plugin to add compile time CRC's but that requires non-mainline Rust.
            1 =>
            {
                *out_iface = this as *mut ::libc::c_void;
                iTestPlugin_add_ref(this);
                gom::OK
            },
            _ =>
            {
                *out_iface = 0 as *mut ::libc::c_void;
                gom::UNKNOWN_INTERFACE
            }
        }
    }
}

// *****************
static TEST_CLASS_INSTANCE_VTABLE: plugin::iClassInstance_Vtbl = plugin::iClassInstance_Vtbl
{
    AddRef: add_ref,
    Release: release,
    Cast: cast,
    CreateInstance: test_create
};

extern "stdcall" fn add_ref(this: *mut plugin::iClassInstance) -> i32
{
    unsafe
    {
        println!("Add ref'd the test rust class instance.");
        (*this).ref_count += 1;
        (*this).ref_count
    }
}
extern "stdcall" fn release(this: *mut plugin::iClassInstance) -> i32
{
    unsafe
    {
        println!("Released the test rust class instance.");
        (*this).ref_count -= 1;
        if (*this).ref_count == 0
        {
            Box::from_raw(this);
            return 0;
        }
        (*this).ref_count
    }
}
extern "stdcall" fn cast(
    this: *mut plugin::iClassInstance,
    iid: u64,
    out_iface: *mut *mut ::libc::c_void) -> u32
{
    unsafe
    {
        match iid
        {
            // This should not be needed...
            1 =>
            {
                *out_iface = this as *mut ::libc::c_void;
                add_ref(this);
                gom::OK
            },
            _ =>
            {
                *out_iface = 0 as *mut ::libc::c_void;
                gom::UNKNOWN_INTERFACE
            }
        }
    }
}

extern "stdcall" fn test_create(
    _this: *mut plugin::iClassInstance,
    _registry: *mut plugin::iRegistry,
    _outer: *mut gom::iBase,
    out_iface: *mut *mut gom::iBase) -> u32
{
    println!("Attempting to create the test rust plugin.");
    unsafe
    {
        *out_iface = Box::into_raw(Box::new(iTestPlugin {vtbl: &TEST_PLUGIN_VTABLE, ref_count: 1})) as *mut gom::iBase;
    }
    gom::OK
}

// **************************
#[no_mangle]
pub extern "stdcall" fn Install(registry: *mut plugin::iRegistry) -> u32
{
    unsafe
    {
        let regy: *const plugin::iRegistry_Vtbl = (*registry).vtbl;
        let result = Box::into_raw(
            Box::new(plugin::iClassInstance {vtbl: &TEST_CLASS_INSTANCE_VTABLE, ref_count: 1})
            );
        ((*regy).Install)(registry, 1, result as *mut plugin::iClassInstance)
    }
}

#[no_mangle]
pub extern "stdcall" fn CanUnload() -> u32
{
	gom::OK
}

#[no_mangle]
pub extern "stdcall" fn Remove(registry: *mut plugin::iRegistry) -> u32
{
    unsafe
    {
        let regy: *const plugin::iRegistry_Vtbl = (*registry).vtbl;
        ((*regy).Remove)(registry, 1)
    }
}

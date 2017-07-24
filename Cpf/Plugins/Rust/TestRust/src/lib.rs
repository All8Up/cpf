#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

#[macro_use]
mod cpf;
use cpf::*;
extern crate libc;

// *****************
gom_implement!(
    interface iTestPlugin : gom::iUnknown
    {
        vtable: iTestPlugin_Vtbl;
        members: {
            ref_count: i32,
        }
        fn test() -> u32;
    }
);

static TEST_PLUGIN_VTABLE: iTestPlugin_Vtbl = iTestPlugin_Vtbl
{
    base: gom::iUnknown_Vtbl
    {
        add_ref: iUnknown_add_ref,
        release: iUnknown_release,
        query_interface: iUnknown_query_interface
    },
    test: iTestPlugin_test
};

struct test{
    ref_count: i32
}

extern "stdcall" fn iUnknown_add_ref(this: *mut gom::iUnknown) -> i32
{
    unsafe
    {
        println!("AddRef'd the test rust instance.");
        let ref mut This: iTestPlugin = *(this as *mut iTestPlugin);
        This.ref_count += 1;
        This.ref_count
    }
}
extern "stdcall" fn iUnknown_release(this: *mut gom::iUnknown) -> i32
{
    unsafe
    {
        println!("Released the test rust instance.");
        let ref mut This: iTestPlugin = *(this as *mut iTestPlugin);
        This.ref_count -= 1;
        if This.ref_count == 0
        {
            println!("Deleting the test rust instance.");
            Box::from_raw(This);
            return 0;
        }
        This.ref_count
    }
}
extern "stdcall" fn iUnknown_query_interface(this: *mut gom::iUnknown, iid: u64, out_iface: *mut *mut ::libc::c_void) -> u32
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
                ((*(*this).vtbl).add_ref)(this);
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

extern "stdcall" fn iTestPlugin_test(_this: *mut iTestPlugin) -> u32
{
    5
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
    _outer: *mut gom::iUnknown,
    out_iface: *mut *mut gom::iUnknown) -> u32
{
    println!("Attempting to create the test rust plugin.");
    unsafe
    {
        *out_iface = Box::into_raw(Box::new(iTestPlugin {vtbl: &TEST_PLUGIN_VTABLE, ref_count: 1})) as *mut gom::iUnknown;
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
pub extern "stdcall" fn Remove(registry: *mut plugin::iRegistry) -> u32
{
    unsafe
    {
        let regy: *const plugin::iRegistry_Vtbl = (*registry).vtbl;
        ((*regy).Remove)(registry, 1)
    }
}

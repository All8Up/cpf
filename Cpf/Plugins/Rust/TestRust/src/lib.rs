#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

#[macro_use]
mod cpf;
use cpf::*;
extern crate libc;
use libc::{c_void};

extern crate log;
extern crate env_logger;

#[repr(C)]
#[derive(Debug)]
pub struct iClassInstance
{
    pub vtable: *const iClassInstanceVTable
}

#[repr(C)]
pub struct iClassInstanceVTable
{
    pub base: gom::iUnknownVTable,    
    pub CreateInstance: extern "stdcall" fn(*mut iClassInstance, registry : *mut plugin::iRegistry, outer : *mut gom::iUnknown, outInstance : *mut *mut gom::iUnknown) -> u32    
}

gom_interface!(
	impl TestRustPlugin: iTestRustPlugin: "Cpf::Rust::iTestRustPlugin",
	iTestRustPluginVTable,
	methods
	{
		fn test(value: u32) -> u32;
	}
);

gom_impl!(
	TestRustPlugin: iTestRustPluginVTable
	{
		test_value: u32,
		registry: IntrusivePtr<plugin::iRegistry>,
	}
);

impl TestRustPlugin
{
	fn new(registry: *mut plugin::iRegistry) -> *mut *const iTestRustPluginVTable
	{
        let result = Box::into_raw(
        	Box::new(
        		TestRustPlugin
        		{
        			vtable: &TEST_RUST_PLUGIN_VTBL,
        			ref_count: 1,
        			test_value: 0,
        			registry: IntrusivePtr::from_raw(registry)
        		}
        		)
        	);
        result as *mut *const iTestRustPluginVTable
	}

	extern "stdcall" fn test(inst: *mut iTestRustPlugin, value: u32) -> u32
	{
		unsafe
		{
	        let this : *mut TestRustPlugin = inst as *mut TestRustPlugin;

			println!("Calling test function with value: {}", value);
			(*this).test_value += value;
			println!("Test function result value: {}", (*this).test_value);
			println!("Test if this class exists in registry: {}", if (*this).registry.exists(1) == gom::OK {true} else {false});
			(*this).test_value
		}
	}
}

// Global vtable for test plugin.
static TEST_RUST_PLUGIN_VTBL : iTestRustPluginVTable = iTestRustPluginVTable
{
	base: gom::iUnknownVTable
	{
		add_ref: iTestRustPluginVTable::add_ref,
		release: iTestRustPluginVTable::release,
		query_interface: iTestRustPluginVTable::query_interface
	},
	test: TestRustPlugin::test
};

// *****************
static TEST_CLASS_INSTANCE_VTABLE: plugin::iClassInstanceVTable = plugin::iClassInstanceVTable
{
	base: gom::iUnknownVTable
	{
	    add_ref: plugin::iClassInstanceVTable::add_ref,
	    release: plugin::iClassInstanceVTable::release,
	    query_interface: plugin::iClassInstanceVTable::query_interface,
	},
    CreateInstance: plugin::iClassInstanceVTable::create
};

impl plugin::iClassInstanceVTable
{
    extern "stdcall" fn add_ref(inst: *mut gom::iUnknown) -> i32
    {
        unsafe
        {
            let this : *mut TestClassInstance = inst as *mut TestClassInstance;
            (*this).ref_count += 1;
            (*this).ref_count
        }
    }

    extern "stdcall" fn release(inst: *mut gom::iUnknown) -> i32
    {
        unsafe
        {
            let this : *mut TestClassInstance = inst as *mut TestClassInstance;
            (*this).ref_count -= 1;
            if (*this).ref_count == 0
            {
                Box::from_raw(this);
                return 0;
            }
            (*this).ref_count
        }
    }

	extern "stdcall" fn query_interface(
	    _this: *mut gom::iUnknown,
	    _iid: u64,
	    _out_iface: *mut *mut ::libc::c_void) -> u32
	{
	    gom::NOT_IMPLEMENTED
	}

	extern "stdcall" fn create(
	    _this: *mut plugin::iClassInstance,
	    registry: *mut plugin::iRegistry,
	    _outer: *mut gom::iUnknown,
	    out_iface: *mut *mut gom::iUnknown) -> u32
	{
	    println!("Attempting to create the test rust plugin.");
	    unsafe
	    {
	    	*out_iface = TestRustPlugin::new(registry) as *mut gom::iUnknown;
	    }
	    gom::OK
	}
}

struct TestClassInstance
{
	vtable: *const plugin::iClassInstanceVTable,
	ref_count: i32
}

impl TestClassInstance
{
	fn new() -> *mut *const plugin::iClassInstanceVTable
	{
        let result = Box::into_raw(
        	Box::new(
        		TestClassInstance
        		{
        			vtable: &TEST_CLASS_INSTANCE_VTABLE,
        			ref_count: 1
        		}
        		)
        	);
        result as *mut *const plugin::iClassInstanceVTable
	}
}

// **************************
#[no_mangle]
pub extern "stdcall" fn Install(registry: *mut plugin::iRegistry) -> u32
{
    unsafe
    {
    	env_logger::init().unwrap();

        let regy: *const plugin::iRegistryVTable = (*registry).vtable;
        let result = TestClassInstance::new();
        ((*regy).install)(registry, 1, result as *mut plugin::iClassInstance)
    }
}

#[no_mangle]
pub extern "stdcall" fn Remove(registry: *mut plugin::iRegistry) -> u32
{
    unsafe
    {
        let regy: *const plugin::iRegistryVTable = (*registry).vtable;
        ((*regy).remove)(registry, 1)
    }
}

#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
extern crate libc;
use libc::{c_char};
//use std::ffi::CStr;


pub struct iRegistry_Vtbl
{
	Load: extern fn(registry: *const iRegistry, name: *const c_char),
	CanUnload: extern fn(registry: *const iRegistry, name: *const c_char),
	Unload: extern fn(registry: *const iRegistry, name: *const c_char)
}

pub struct iRegistry
{
	vtbl: *const iRegistry_Vtbl
}


#[no_mangle]
pub extern "stdcall" fn Install(registry: *const iRegistry) -> u32
{
	return 0;
}

#[no_mangle]
pub extern "stdcall" fn CanUnload() -> u32
{
	return 0;
}

#[no_mangle]
pub extern "stdcall" fn Remove(registry: *const iRegistry) -> u32
{
	return 0;
}

#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use libc::{c_void};

#[repr(C)]
pub struct iBase_Vtbl
{
    AddRef: extern "stdcall" fn() -> u32,
    Release: extern "stdcall" fn() -> u32,
    Cast: extern "stdcall" fn(id: u64, outIface: *mut *mut c_void) -> u32,
}

#[derive(Debug)]
#[repr(C)]
pub struct iBase
{
	pub vtbl: *const iBase_Vtbl
}

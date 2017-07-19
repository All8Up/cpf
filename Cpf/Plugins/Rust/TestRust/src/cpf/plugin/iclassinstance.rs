#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use gom::*;
use plugin::*;

pub struct iClassInstance_Vtbl
{
    pub AddRef: extern "stdcall" fn(
    	this: *mut iClassInstance
  		) -> i32,
    pub Release: extern "stdcall" fn(
    	this: *mut iClassInstance
    	) -> i32,
    pub Cast: extern "stdcall" fn(
    	this: *mut iClassInstance,
    	id: u64,
    	outIface: *mut *mut ::libc::c_void
    	) -> u32,
    pub CreateInstance: extern "stdcall" fn(
    	this: *mut iClassInstance,
    	registry: *mut iRegistry,
    	outer: *mut iBase,
    	outIface: *mut *mut iBase
    	) -> u32,
}
pub struct iClassInstance
{
	pub vtbl: *const iClassInstance_Vtbl,
	pub ref_count: i32
}

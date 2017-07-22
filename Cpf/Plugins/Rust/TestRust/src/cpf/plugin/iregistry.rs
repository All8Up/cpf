#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use cpf::*;

#[repr(C)]
pub struct iRegistry_Vtbl
{
    pub AddRef: extern "stdcall" fn(this: *mut iRegistry) -> i32,
    pub Release: extern "stdcall" fn(this: *mut iRegistry) -> i32,
    pub Cast: extern "stdcall" fn(this: *mut iRegistry, id: u64, outIface: *mut *mut ::libc::c_void) -> u32,
    pub Load: extern "stdcall" fn(this: *mut iRegistry, library: *const ::libc::c_char) -> u32,
    pub Unload: extern "stdcall" fn(this: *mut iRegistry, library: *const ::libc::c_char) -> u32,
    pub Install: extern "stdcall" fn(this: *mut iRegistry, cid: u64, clsInst: *mut plugin::iClassInstance) -> u32,
    pub Remove: extern "stdcall" fn(this: *mut iRegistry, cid: u64) -> u32,
    pub GetClassInstance: extern "stdcall" fn(this: *mut iRegistry, cid: u64, clsInst: *mut plugin::iClassInstance) -> u32,
    pub Exists: extern "stdcall" fn(this: *mut iRegistry, cid: u64) -> u32,
    pub Create: extern "stdcall" fn(this: *mut iRegistry, outer: *mut gom::iUnknown, cid: u64, iid: u64, outIFace: *mut *mut ::libc::c_void) -> u32,
    pub ClassInstall: extern "stdcall" fn(this: *mut iRegistry, count: i32, pairs: *const gom::IID_CID) -> u32,
    pub ClassRemove: extern "stdcall" fn(this: *mut iRegistry, count: i32, pairs: *const gom::IID_CID) -> u32,
    pub GetClasses: extern "stdcall" fn(this: *mut iRegistry, id: u64, count: i32, cid: u64) -> u32,
    pub InstanceInstall: extern "stdcall" fn(this: *mut iRegistry, id: u64, instance: *mut gom::iUnknown) -> u32,
    pub InstanceRemove: extern "stdcall" fn(this: *mut iRegistry, id: u64) -> u32,
    pub GetInstance: extern "stdcall" fn(this: *mut iRegistry, id: u64, outIface: *mut gom::iUnknown) -> u32,
}

#[derive(Debug)]
#[repr(C)]
pub struct iRegistry
{
	pub vtbl: *const iRegistry_Vtbl
}

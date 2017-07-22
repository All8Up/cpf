#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use libc::{c_void};
use cpf::*;

#[derive(Debug)]
#[repr(C)]
pub struct iUnknown
{
	pub vtbl: *const iUnknown_Vtbl
}

#[repr(C)]
pub struct iUnknown_Vtbl
{
    pub add_ref: extern "stdcall" fn(*mut iUnknown) -> i32,
    pub release: extern "stdcall" fn(*mut iUnknown) -> i32,
    pub query_interface: extern "stdcall" fn(*mut iUnknown, iid: u64, out_iface: *mut *mut c_void) -> u32,
}

impl iUnknown
{
	pub unsafe fn add_ref(&mut self) -> i32 { ((*self.vtbl).add_ref)(self) }
	pub unsafe fn release(&mut self) -> i32 { ((*self.vtbl).release)(self) }
	pub unsafe fn query_interface(&mut self, iid: u64, out_iface: *mut *mut c_void) -> u32 { ((*self.vtbl).query_interface)(self, iid, out_iface) }
}

unsafe impl AsPtr<iUnknown> for iUnknown {}

unsafe impl ::GomInterface for iUnknown
{
    type Vtable = iUnknown_Vtbl;
}

/*
extern {
    static IID_IUnknown: IID;
}


unsafe impl ::ComInterface for IUnknown {
    #[doc(hidden)]
    type Vtable = IUnknownVtbl;
    fn iid() -> ::IID { unsafe { IID_IUnknown } }
}
*/

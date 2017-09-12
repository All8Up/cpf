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
	pub vtable: *const iUnknownVTable
}

#[repr(C)]
pub struct iUnknownVTable
{
    pub add_ref: extern "stdcall" fn(*mut iUnknown) -> i32,
    pub release: extern "stdcall" fn(*mut iUnknown) -> i32,
    pub query_interface: extern "stdcall" fn(*mut iUnknown, iid: u64, out_iface: *mut *mut c_void) -> u32,
}

pub trait Unknown
{
    fn add_ref(&mut self) -> i32;
    fn release(&mut self) -> i32;
    fn query_interface(&mut self, iid: u64, out_iface: *mut *mut c_void) -> u32;
}

impl Unknown for iUnknown
{
	fn add_ref(&mut self) -> i32
    {
        unsafe
        {
            ((*self.vtable).add_ref)(self)
        }
    }
	fn release(&mut self) -> i32
    {
        unsafe
        {
            ((*self.vtable).release)(self)
        }
    }
	fn query_interface(&mut self, iid: u64, out_iface: *mut *mut c_void) -> u32
    {
        unsafe
        {
            ((*self.vtable).query_interface)(self, iid, out_iface)
        }
    }
}

unsafe impl AsPtr<iUnknown> for iUnknown {}

unsafe impl ::GomInterface for iUnknown
{
    type Vtable = iUnknownVTable;
}

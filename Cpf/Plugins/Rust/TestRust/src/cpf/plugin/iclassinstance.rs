#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use libc::{c_void};
use cpf::*;


gom_interface!(
    iClassInstance : "Cpf::Plugin::iClassInstance",
    iClassInstanceVTable,
    methods
    {
	    fn CreateInstance(
	    	registry: *mut plugin::iRegistry,
	    	outer: *mut gom::iUnknown,
	    	outIface: *mut *mut gom::iUnknown
	    	) -> u32;
    }
);

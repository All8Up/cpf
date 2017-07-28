#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate libc;
use cpf::*;
use libc::{c_void};

gom_interface!(
    iRegistry : "Cpf::GOM::iRegistry",
    iRegistryVTable,
    methods
    {
        fn load(library: *const ::libc::c_char) -> u32;
        fn unload(library: *const ::libc::c_char) -> u32;
        fn install(cid: u64, clsInst: *mut plugin::iClassInstance) -> u32;
        fn remove(cid: u64) -> u32;
        fn get_class_instance(cid: u64, clsInst: *mut plugin::iClassInstance) -> u32;
        fn exists(cid: u64) -> u32;
        fn create(outer: *mut gom::iUnknown, cid: u64, iid: u64, outIFace: *mut *mut ::libc::c_void) -> u32;
        fn class_install(count: i32, pairs: *const gom::IID_CID) -> u32;
        fn class_remove(count: i32, pairs: *const gom::IID_CID) -> u32;
        fn get_classes(id: u64, count: i32, cid: u64) -> u32;
        fn instance_install(id: u64, instance: *mut gom::iUnknown) -> u32;
        fn instance_remove(id: u64) -> u32;
        fn get_instance(id: u64, outIface: *mut gom::iUnknown) -> u32;
    }
);

#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(dead_code)]

extern crate clap;
use clap::{Arg, App};
use std::env;
use std::fs::File;
use std::io::prelude::*;
pub mod grammar;
pub mod ast;
pub mod lexer;
pub mod gen;
pub mod crc;
pub mod context;
use context::*;

#[test]
fn test_idl()
{
}

/*
*/
extern crate libc;

mod CPF
{
    mod GOM
    {
        const OK: u32 = 0x72D622E4;      // Sub-system: "Core" Code: "OK"
        const IN_USE: u32 = 0x72D65159;      // Sub-system: "Core" Code: "InUse"
        const ERROR: u32 = 0xF2D60ECC;      // Sub-system: "Core" Code: "Error"
        const UNKNOWN_INTERFACE: u32 = 0xF2D623E7;      // Sub-system: "Core" Code: "UnknownInterface"
        const INVALID_PARAMETER: u32 = 0xF2D60CEA;      // Sub-system: "Core" Code: "InvalidParameter"
        const OUT_OF_MEMORY: u32 = 0xF2D655B8;      // Sub-system: "Core" Code: "OutOfMemory"
        const UNKNOWN_CLASS: u32 = 0xF2D67F71;      // Sub-system: "Core" Code: "UnknownClass"
        const NOT_IMPLEMENTED: u32 = 0xF2D67EFE;      // Sub-system: "Core" Code: "NotImplemented"
        const INVALID: u32 = 0xF2D63EDB;      // Sub-system: "Core" Code: "Invalid"
        const NOT_ENOUGH_SPACE: u32 = 0xF2D6075E;      // Sub-system: "Core" Code: "NotEnoughSpace"
        const NOT_INITIALIZED: u32 = 0xF2D66D72;      // Sub-system: "Core" Code: "NotInitialized"
        const INITIALIZATION_FAILURE: u32 = 0xF2D66346;      // Sub-system: "Core" Code: "InitializationFailure"
        const OUT_OF_RANGE: u32 = 0xF2D6436A;      // Sub-system: "Core" Code: "OutOfRange"
        const DUPLICATE: u32 = 0xF2D675B4;      // Sub-system: "Core" Code: "Duplicate"
        const REGISTRY_ERROR: u32 = 0xF2D62784;      // Sub-system: "Core" Code: "RegistryError"
        const NOT_RUNNING: u32 = 0xF2D67C4C;      // Sub-system: "Core" Code: "NotRunning"

        pub struct iBase_Vtbl
        {
            AddRef: extern fn() -> u32,
            Release: extern fn() -> u32,
            Cast: extern fn(id: u64, outIface: ::libc::c_void) -> u32,
        }
        pub struct iBase
        {
        }
        pub struct IID_CID
        {}

        pub struct iClassInstance {}
    }
    mod Plugin
    {
        pub struct iRegistry_Vtbl
        {
            Load: extern fn(library: ::libc::c_char) -> u32,
            CanUnload: extern fn(library: ::libc::c_char) -> u32,
            Unload: extern fn(library: ::libc::c_char) -> u32,
            Install: extern fn(cid: u64, clsInst: ::CPF::GOM::iClassInstance) -> u32,
            Remove: extern fn(cid: u64) -> u32,
            GetClassInstance: extern fn(cid: u64, clsInst: ::CPF::GOM::iClassInstance) -> u32,
            Exists: extern fn(cid: u64) -> u32,
            Create: extern fn(outer: ::CPF::GOM::iBase, cid: u64, iid: u64, outIFace: ::libc::c_void) -> u32,
            ClassInstall: extern fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            ClassRemove: extern fn(count: i32, pairs: ::CPF::GOM::IID_CID) -> u32,
            GetClasses: extern fn(id: u64, count: i32, cid: u64) -> u32,
            InstanceInstall: extern fn(id: u64, instance: ::CPF::GOM::iBase) -> u32,
            InstanceRemove: extern fn(id: u64) -> u32,
            GetInstance: extern fn(id: u64, outIface: ::CPF::GOM::iBase) -> u32,
        }
    }
}


// TODO:
//	Write a custom lexer for the following:
//		Handle comments.
//		Handle import processing.

fn main()
{
	let command_line = App::new("IDL")
		.version("0.1")
		.about("Generate language bindings from IDL descriptions.")
		.arg(Arg::with_name("INPUT")
			.short("i")
			.long("input")
			.help("Input IDL file to process.")
			.required(true)
			.takes_value(true)
			)
		.arg(Arg::with_name("OUTPUT")
			.short("o")
			.long("output")
			.help("Generated output.")
			.required(true)
			.takes_value(true)
			)
		.arg(Arg::with_name("LANGUAGE")
			.short("l")
			.long("language")
			.help("Language of generated output, can be one of: rust, cpp or python3.")
			.required(true)
			.takes_value(true)
			)
		.arg(Arg::with_name("VERBOSE")
			.short("v")
			.long("verbose")
			.help("Output verbose debug information.")
			)
		.get_matches();

	let language_value = language_from_str(command_line.value_of("LANGUAGE").unwrap());
	if language_value == Language::Unknown
	{
		println!("Invalid language generation requested.");
		return
	}

	let configuration : Configuration = Configuration::new(
		env::current_dir().unwrap(),
		command_line.value_of("INPUT").unwrap(),
		command_line.value_of("OUTPUT").unwrap(),
		language_value,
		command_line.is_present("VERBOSE")
	);

	let generator = gen::get_generator(configuration.language).unwrap();
	let mut context = Context::new(configuration, generator);

	context.log();

	let file_result = File::open(context.get_configuration().get_input_filename());
	match file_result
	{
		Err(e) => {
			println!("Error: {}", e);
		},
		Ok(mut file) =>
		{
			let mut contents = String::new();
			match file.read_to_string(&mut contents)
			{
				Err(e) => {
					println!("Error: {:?}", e);
				},
				Ok(_) =>
				{
					println! ("------------------------------- Parsing IDL.");
					match grammar::parse_IDL(&contents)
					{
						Err(e) =>
						{
							println!("Error: {:?}", e);
						},
						Ok(tree) =>
						{
							let output_filename = context.get_configuration().get_output_filename().clone();
							context.get_generator().generate(tree, &output_filename);
							println! ("-------------------------------");
						}
					}
				}
			}
		}
	}
}

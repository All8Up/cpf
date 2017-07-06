extern crate clap;
use clap::{Arg, App}; //, SubCommand};
use std::env;
use std::fs::File;
use std::io::prelude::*;
pub mod grammar;
pub mod ast;
pub mod lexer;
pub mod gen;
pub mod crc;

#[test]
fn test_idl()
{
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

	let current_dir = env::current_dir().unwrap();
	let input_file = command_line.value_of("INPUT").unwrap();
	let output_file = command_line.value_of("OUTPUT").unwrap();
	let language = command_line.value_of("LANGUAGE").unwrap();
	let verbose = command_line.is_present("VERBOSE");

	if verbose
	{
		println!("Current working directory: {:?}", current_dir);
		println!("Input: {}", input_file);
		println!("Output: {}", output_file);
		println!("Language: {}", language);
		println!("Verbose: {}", verbose);
	}

	let selected_generator : Option<Box<gen::CodeGenerator>> = match language
	{
		"rust" => {gen::get_generator(gen::Language::Rust)},
		"cpp" => {gen::get_generator(gen::Language::Cpp)},
		"python3" => {gen::get_generator(gen::Language::Python3)},
		_ => {None}
	};
	if selected_generator.is_none()
	{
		println!("Invalid language generation requested.");
		return
	}
	let generator = selected_generator.unwrap();

	let file_result = File::open(input_file);
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
							generator.generate(tree, output_file);
							println! ("-------------------------------");
						}
					}
				}
			}
		}
	}
}

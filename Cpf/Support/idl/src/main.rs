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

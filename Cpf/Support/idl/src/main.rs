extern crate clap;
use clap::{Arg, App}; //, SubCommand};
use std::env;
use std::fs::File;
use std::io::prelude::*;
pub mod idl;
pub mod ast;
use ast::{NodeRef, Data};
pub mod lexer;
use lexer::{LexicalError};

#[test]
fn test_idl()
{
}

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
			.help("Language of generated output.")
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
					match idl::parse_IDL(&contents)
					{
						Err(e) =>
						{
							println!("Error: {:?}", e);
						},
						Ok(tree) =>
						{
							display_ast(tree.clone());
							println! ("-------------------------------");
						}
					}
				}
			}
		}
	}
}

fn display_ast(tree: NodeRef<Data>)
{
	println!("------------------------");
	display_siblings(tree, 0);
	println!("------------------------");
}

fn display_siblings(tree: NodeRef<Data>, indent: usize)
{
	let mut current = tree.clone();
	loop
	{
		display_indented(&current, indent);
		display_children(current.clone(), indent+2);

		let sibling = current.next_sibling();
		if sibling.is_none() {return}
		current = sibling.unwrap();
	}
}

fn display_children(tree: NodeRef<Data>, indent: usize)
{
	let mut current = tree.clone();

	let child = current.first_child();
	if child.is_none() {return}
	current = child.unwrap();

	display_siblings(current.clone(), indent);
}

fn display_indented(node: &NodeRef<Data>, indent: usize)
{
	println!("{:indent$}{:?}", "", node, indent=indent);
}

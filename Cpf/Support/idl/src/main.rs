extern crate clap;
use clap::{Arg, App, SubCommand};
pub mod idl;
pub mod ast;

#[test]
fn test_idl()
{
}

fn main()
{
	let command_line = App::new("IDL")
		.version("0.1")
		.author("K Brock <toolzer@gmail.com>")
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

	let input_file = command_line.value_of("INPUT").unwrap();
	let output_file = command_line.value_of("OUTPUT").unwrap();
	let language = command_line.value_of("LANGUAGE").unwrap();
	let verbose = command_line.is_present("VERBOSE");

	println!("Input: {}", input_file);
	println!("Output: {}", output_file);
	println!("Language: {}", language);
	println!("Verbose: {}", verbose);

	// Not sure that imports are needed given the ability to forward reference.
	let test_string =
	"import \"something\"

	interface iTest;

	namespace test
	{
		namespace test2
		{
			interface iTest2;
			struct DataTest;
			interface iBlargo : test::test2::iTest2
			{
				interface_id iid('test::test2::iBlargo');

				i64 Read([out] void* dst, size_t size);
				i64 Write([in] const void* src, size_t size);
			}
			class_id iBlargoCID('test::test2::iBlargo');

			namespace test3
			{
			}
		}
	}";

	println! ("------------------------------- Parsing IDL.");
	let result = idl::parse_IDL(test_string);
	match result
	{
		Ok(tree) =>
		{
			display_ast(tree.clone());
		},
		Err(e) =>
		{
			println! ("Parsing error: {:?}", e);
		}
	}

	println! ("-------------------------------");
}

fn display_ast(tree: ast::NodeRef<ast::Data>)
{
	println!("------------------------");
	display_siblings(tree, 0);
	println!("------------------------");
}

fn display_siblings(tree: ast::NodeRef<ast::Data>, indent: usize)
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

fn display_children(tree: ast::NodeRef<ast::Data>, indent: usize)
{
	let mut current = tree.clone();

	let child = current.first_child();
	if child.is_none() {return}
	current = child.unwrap();

	display_siblings(current.clone(), indent);
}

fn display_indented(node: &ast::NodeRef<ast::Data>, indent: usize)
{
	println!("{:indent$}{:?}", "", node, indent=indent);
}

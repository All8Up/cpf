pub mod idl;
pub mod ast;

#[test]
fn test_idl()
{
}

fn main()
{
	let test_string =
	"import \"something\"

	interface iTest;

	namespace test
	{
		namespace test2
		{
			interface iTest2;
			interface iBlargo : test::test2::iTest2
			{
				interface_id iid('test::test2::iBlargo');
				[in] u8
				[in, out] const i8*
				[out] u16
				[out, in] i32
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

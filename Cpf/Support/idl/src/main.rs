pub mod idl;
pub mod ast;

#[test]
fn test_idl()
{
	let result = idl::parse_Numeric("123");
	match *result.unwrap()
	{
		ast::Numeric::Signed(value) => {println!("Value: {}", value);},
		ast::Numeric::Unsigned(value) => {println!("Value: {}", value);},
		ast::Numeric::Float(value) => {println!("Value: {}", value);}
	}
	println!("--------------");
}

fn main()
{
	/*
	let result = idl::parse_Numeric("123");
	match *result.unwrap()
	{
		ast::Numeric::Signed(value) => {println!("Value: {}", value);},
		ast::Numeric::Unsigned(value) => {println!("Value: {}", value);},
		ast::Numeric::Float(value) => {println!("Value: {}", value);}
	}
	*/

	let mut test_tree = ast::Tree::new();
	let root_node = test_tree.create_node(ast::Data::Namespace {name: "test"});
	test_tree.set_root(root_node);
	let child_node = test_tree.create_node(ast::Data::Namespace {name: "child"});
	test_tree.add_child(root_node, child_node);

	println! ("Tree: {:?}", test_tree);
	for node in &test_tree
	{
		println! ("Node idx: {:?}", node);
	}

	/*
	println! ("Node idx: {}", root_node);
	println! ("Child node idx: {}", child_node);
	*/
}

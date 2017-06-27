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
	let test_string =
	"import something

	interface iTest;

	namespace test
	{
		namespace test2
		{
			interface iTest2;
			interface iBlargo : test::test2::iTest2
			{
				interface_id iid('test::test2::iBlargo');
			}
			class_id iBlargoCID('test::test2::iBlargo');

			namespace test3
			{
			}
		}
	}";

	println! ("------------------------------- Parsing IDL.");
	let result = idl::parse_IDL(test_string);
	for node in result.unwrap().depth_first()
	{
		println!("{:?}", node);
	}

	/*
	match result
	{
		Some(tree) =>
		{
			for node in tree.depth_first()
			{
				println!("{:?}", node);
			}
		},
		None =>
		{
			println! ("Parsing error.");
		}
	}
	*/
	println! ("-------------------------------");
}

pub mod idl;
pub mod ast;

#[test]
fn test_idl()
{
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
	match result
	{
		Ok(tree) =>
		{
			for node in tree.depth_first()
			{
				println!("{:?}", node);
			}
		},
		Err(e) =>
		{
			println! ("Parsing error: {:?}", e);
		}
	}

	println! ("-------------------------------");
}

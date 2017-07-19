use ast::*;
use gen::code_gen::{CodeGenerator, ConstType};
use gen::scope::*;
use context::*;
use crc::*;


// ------------------------
pub struct Generator
{
	tree: ASTRef,
	scopes: Scopes,
	current_scope: usize,
	indent: usize
}

impl CodeGenerator for Generator
{
	fn log(&self, _: &Context)
	{
	}

	fn string_out(&mut self, s: &str)
	{
		println!("{}", s);
	}

	fn indent_out(&mut self, s: &str)
	{
		println!("{:indent$}{}", "", s, indent=self.indent*4);
	}

	fn indent(&mut self)
	{
		self.indent += 1;
	}

	fn unindent(&mut self)
	{
		self.indent -= 1;
	}

    fn preamble(&mut self, _tree: &ASTRef, _output: &str)
    {
        self.string_out(
            "#![allow(non_snake_case)]\n#![allow(non_camel_case_types)]\n#![allow(dead_code)]\n\nextern crate libc;\n"
        );
    }

	fn generate(&mut self, tree: ASTRef, output: &str)
	{
		println!("Generating rust code to: {}", output);
		self.preamble(&tree, output);
		self.traverse(tree.clone(), |_, _| -> () {});
		self.tree = tree;
	}

	fn push_scope(&mut self, name: &str)
	{
//		let scope = Scope::new(name);
		self.indent_out(&format!("mod {}", name));
		self.indent_out("{");
		self.indent += 1;
	}

	fn pop_scope(&mut self)
	{
		self.indent -= 1;
		self.indent_out("}");
	}

	fn get_scope(&self) -> Scope
	{
		self.scopes.get_scope(self.current_scope)
	}

	fn handle_const_result(&mut self, const_result: &ConstResult, _node: ASTRef) -> bool
	{
		let value: u32 = if const_result.is_error == true {0x80000000} else {0} |
			(crc16(&const_result.sub_system) as u32) << 15 | (crc15(&const_result.code) as u32);
		let left = format!("const {}", const_result.name);
		self.indent_out(&format!(
			"{:<38} : u32 = 0x{:8X};      // Sub-system: \"{}\" Code: \"{}\"",
			left, value, const_result.sub_system, const_result.code));

		true
	}

	fn add_constant(&mut self, _: ConstType, name: &str, value: u32) -> bool
	{
		self.indent_out(&format!("const {} : u32 = 0x{:8X};", name, value));
		true
	}

	fn data_type_to_string(&self, data_type: DataType) -> String
	{
		return match data_type
			{
				DataType::U8 => "uint8_t".to_string(),
				DataType::I8 => "int8_t".to_string(),
				DataType::U16 => "uint16_t".to_string(),
				DataType::I16 => "int16_t".to_string(),
				DataType::U32 => "u32".to_string(),
				DataType::I32 => "i32".to_string(),
				DataType::U64 => "u64".to_string(),
				DataType::I64 => "i64".to_string(),
				DataType::F32 => "f32".to_string(),
				DataType::F64 => "f64".to_string(),
				DataType::Char => "c_char".to_string(),
				DataType::WChar => "wchar_t".to_string(),
				DataType::Void => "void".to_string(),
				DataType::SizeT => "size_t".to_string(),
				DataType::Result => "u32".to_string(),
				DataType::NamedType { ref name } => name.to_string()
			}
	}

	fn handle_interface(&mut self, iface: &Interface, _node: ASTRef) -> bool
	{
		// 	Load: extern fn(registry: *const iRegistry, name: *const c_char),
		self.string_out("");
		self.indent_out(&format!("pub struct {}_Vtbl", iface.name));
		self.indent_out("{");
		self.indent();
		for stmt in iface.statements.iter()
			{
				match stmt
					{
						&InterfaceStatement::IID {value: ref v} =>
							self.indent_out(&format!("iid: {}", v)),
						&InterfaceStatement::Method {name: ref n, result_type: ref rt, parameters: ref p} =>
							{
								let mut params : String = "".to_string();
								for param in p
									{
										if !params.is_empty()
											{
												params += ", ";
											}
										params += &param.name;
										params += ": ";

										let dt = param.data_type.data_type.data_type.to_string();
										params += &dt;
									}

								let result = " -> ".to_string() + &rt.data_type.to_string();
								self.indent_out(&format!("{}: extern fn({}){},", n, params, result));
							}
					}
			}
		self.unindent();
		self.indent_out("}");

		true
	}
}

impl Generator
{
	pub fn new() -> Generator
	{
		Generator
		{
			tree: NodeRef::new(Box::new(Comment {content: "".to_string()})),
			scopes: Scopes::new(),
			current_scope: 0,
			indent: 0
		}
	}

	fn traverse<T>(&mut self, tree: ASTRef, child_handler: T)
		where T: Fn(&mut Generator, ASTRef)
	{
		let mut current = tree;
		loop
		{
			// 1. Do something with the current node.
			{
				let ref c = *current.borrow();
				if !c.handle(self, current.clone())
				{
					println!("************* traversal terminated");
					return
				}
			}

			// 2. Walk through children.
			child_handler(self, current.clone());	

			// 3. Move to next sibling, exit if no sibling.
			match current.next_sibling()
			{
				None => return,
				Some(sibling) => current = sibling
			}
		}
	}
}

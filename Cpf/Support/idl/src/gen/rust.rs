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

	fn generate(&mut self, tree: ASTRef, output: &str)
	{
		println!("Generating rust code to: {}", output);
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

	fn add_result(&mut self, name: &str, is_error: bool, subsys: &str, code: &str) -> bool
	{
		let value: u32 = if is_error == true {0x80000000} else {0} |
			(crc16(subsys) as u32) << 15 | (crc15(code) as u32);
		let left = format!("const {}", name);
		self.indent_out(&format!(
			"{:<38} : u32 = 0x{:8X};      // Sub-system: \"{}\" Code: \"{}\"",
			left, value, subsys, code));

		true
	}

	fn add_constant(&mut self, _: ConstType, name: &str, value: u32) -> bool
	{
		self.indent_out(&format!("const {} : u32 = 0x{:8X};", name, value));
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

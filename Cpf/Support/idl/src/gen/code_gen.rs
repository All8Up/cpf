use gen::*;
use ast::*;
use context::*;

pub enum ConstType
{
	U32
}

pub trait Preamble
{
    fn generate(&mut self, generator: &CodeGenerator);
}

pub trait CodeGenerator
{
	fn log(&self, context: &Context);
	fn string_out(&mut self, _: &str) {}
	fn indent_out(&mut self, _: &str) {}
	fn indent(&mut self) {}
	fn unindent(&mut self) {}

	fn preamble(&mut self, _tree: &ASTRef, _output: &str) {}
	fn generate(&mut self, tree: ASTRef, output: &str);
	fn push_scope(&mut self, name: &str);
	fn pop_scope(&mut self);
	fn get_scope(&self) -> Scope {Scope::new("")}
	fn add_constant(&mut self, _: ConstType, _: &str, _: u32) -> bool {true}
	fn data_type_to_string(&self, _data_type: DataType) -> String {return "".to_string();}

    fn handle_const_result(&mut self, _const_result_node: &ConstResult, _node: ASTRef) -> bool {true}
	fn handle_interface(&mut self, _interface_node: &Interface, _node: ASTRef) -> bool {true}
    fn handle_import(&mut self, _import_node: &Import, _node: ASTRef) -> bool {true}
}

pub fn get_generator(language: Language) -> Option<Box<CodeGenerator>>
{
	match language
	{
		Language::Rust => {Some(Box::new(rust::Generator::new()))},
		Language::Python3 => {Some(Box::new(python3::Generator {}))},
		Language::Cpp => {Some(Box::new(cpp::Generator {}))}
		_ => None
	}
}

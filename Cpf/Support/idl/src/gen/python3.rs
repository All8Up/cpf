use ast;
use gen::code_gen::CodeGenerator;
use context::*;

pub struct Generator
{

}

#[allow(unused_variables)]
impl CodeGenerator for Generator
{
	fn log(&self, context: &Context)
	{}

	fn generate(&mut self, tree: ast::ASTRef, output: &str)
	{
		println!("Generating Python 3 code to: {}", output);
	}
	fn push_scope(&mut self, name: &str) {println!("Pushing new scope: {:?}", name);}
	fn pop_scope(&mut self) {println!("Popping scope.");}
}

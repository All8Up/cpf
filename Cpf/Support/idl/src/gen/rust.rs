use ast::*;
use gen::code_gen::CodeGenerator;

pub struct Generator
{

}

impl CodeGenerator for Generator
{
	fn generate(&self, tree: NodeRef<Data>, output: &str)
	{
		println!("Generating rust code to: {}", output);
		display_ast(tree.clone());
	}
}

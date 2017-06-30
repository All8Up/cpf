use gen::code_gen::CodeGenerator;

pub struct Generator
{

}

impl CodeGenerator for Generator
{
	fn generate(&self, output: &str)
	{
		println!("Generating rust code to: {}", output);
	}
}

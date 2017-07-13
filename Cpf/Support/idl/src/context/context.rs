use configuration::*;
use gen::code_gen::CodeGenerator;

pub struct Context
{
	configuration: Configuration,
	generator: Box<CodeGenerator>
}

impl Context
{
	pub fn new(config: Configuration, gen: Box<CodeGenerator>) -> Context
	{
		Context {configuration: config, generator: gen}
	}

	pub fn log(&self)
	{
		if self.configuration.verbose
		{
			self.configuration.log(self);
			self.generator.log(self);
		}
	}

	pub fn get_configuration(&self) -> &Configuration
	{
		&self.configuration
	}

	pub fn get_generator(&mut self) -> &mut Box<CodeGenerator>
	{
		&mut self.generator
	}
}

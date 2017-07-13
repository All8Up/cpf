use std::path::PathBuf;
use context::*;

pub struct Configuration
{
	pub working_directory: PathBuf,
	pub input_file: String,
	pub output_file: String,
	pub language: Language,
	pub verbose: bool
}

impl Configuration
{
	pub fn new(working_dir: PathBuf, input: &str, output: &str, language: Language, verbosity: bool) -> Configuration
	{
		Configuration
		{
			working_directory: working_dir,
			input_file: input.to_string(),
			output_file: output.to_string(),
			language: language,
			verbose: verbosity
		}
	}

	pub fn log(&self, _: &Context)
	{
		println!("Current working directory: {:?}", self.working_directory);
		println!("Input: {}", self.input_file);
		println!("Output: {}", self.output_file);
		println!("Language: {:?}", self.language);
		println!("Verbose: {}", self.verbose);
	}

	pub fn get_input_filename(&self) -> &String
	{
		&self.input_file
	}
	pub fn get_output_filename(&self) -> &String
	{
		&self.output_file
	}
}

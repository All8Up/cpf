#[derive(Clone, Copy, PartialEq, Debug)]
pub enum Language
{
	Unknown,
	Rust,
	Python3,
	Cpp
}

pub fn language_from_str(language: &str) -> Language
{
	match language
	{
		"rust" => return Language::Rust,
		"python3" => return Language::Python3,
		"cpp" => return Language::Cpp,
		_ => return Language::Unknown
	}
}

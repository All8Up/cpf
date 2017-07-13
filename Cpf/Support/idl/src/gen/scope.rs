use std::usize;


// ------------------------
type Handle = usize;
const INVALID_HANDLE: usize = usize::MAX;


// ------------------------
pub struct Scope(String);

impl Scope
{
	pub fn new(name: &str) -> Scope
	{
		Scope(name.to_string())
	}

	pub fn append(&mut self, name: &str)
	{
		let mut result = self.0.clone();
		if !result.is_empty()
		{
			result += "::";
		}
		result += name;
		self.0 = result;
	}
}


// ------------------------
struct ScopeEntry
{
	Scope: Scope,
	children: Vec<usize>,
	parent: usize
}

impl ScopeEntry
{
	fn new(name: &str) -> ScopeEntry
	{
		ScopeEntry {Scope: Scope::new(name), children: vec![], parent: INVALID_HANDLE}
	}
}


// ------------------------
pub struct Scopes
{
	Scope_arena: Vec<ScopeEntry>,
	root: Handle
}

impl Scopes
{
	pub fn new() -> Scopes
	{
		Scopes
		{
			Scope_arena: vec![ScopeEntry::new("")],
			root: INVALID_HANDLE
		}
	}

	fn find(&self, scope: Scope) -> Handle
	{
		INVALID_HANDLE
	}

	fn get_name(&self, handle: Handle) -> &Scope
	{
		return &self.Scope_arena[handle].Scope;
	}

	pub fn get_scope(&self, handle: Handle) -> Scope
	{
		let mut result = Scope::new("");
		let path = self.get_path(handle);
		for element in path
		{
			result.append(&self.Scope_arena[element].Scope.0);
		}
		result
	}

	fn get_path(&self, handle: Handle) -> Vec<Handle>
	{
		let mut result = Vec::new();
		result.push(handle);
		let mut current = handle;
		loop
		{
			let parent = self.Scope_arena[current].parent;
			if parent == INVALID_HANDLE
			{
				return result;
			}
			result.insert(0, parent);
			current = parent;
		}
	}
}

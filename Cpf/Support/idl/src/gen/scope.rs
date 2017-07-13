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
	scope: Scope,
	children: Vec<usize>,
	parent: usize
}

impl ScopeEntry
{
	fn new(name: &str) -> ScopeEntry
	{
		ScopeEntry {scope: Scope::new(name), children: vec![], parent: INVALID_HANDLE}
	}
}


// ------------------------
pub struct Scopes
{
	scope_arena: Vec<ScopeEntry>,
	root: Handle
}

impl Scopes
{
	pub fn new() -> Scopes
	{
		Scopes
		{
			scope_arena: vec![ScopeEntry::new("")],
			root: INVALID_HANDLE
		}
	}

	fn find(&self, _: Scope) -> Handle
	{
		INVALID_HANDLE
	}

	fn get_name(&self, handle: Handle) -> &Scope
	{
		return &self.scope_arena[handle].scope;
	}

	pub fn get_scope(&self, handle: Handle) -> Scope
	{
		let mut result = Scope::new("");
		let path = self.get_path(handle);
		for element in path
		{
			result.append(&self.scope_arena[element].scope.0);
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
			let parent = self.scope_arena[current].parent;
			if parent == INVALID_HANDLE
			{
				return result;
			}
			result.insert(0, parent);
			current = parent;
		}
	}
}

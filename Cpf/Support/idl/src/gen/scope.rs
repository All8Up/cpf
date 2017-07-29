use std::usize;


// ------------------------
type Handle = usize;
const INVALID_HANDLE: usize = usize::MAX;


// ------------------------
#[derive(Debug)]
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
	#[allow(dead_code)]
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
	#[allow(dead_code)]
	root: Handle,
    current_scope: Handle
}

impl Scopes
{
	pub fn new() -> Scopes
	{
        let root = ScopeEntry::new("");
		let result = Scopes
		{
			scope_arena: vec![root],
			root: 0,
            current_scope: 0
		};
        result
	}

    pub fn get_current(&self) -> Handle
    {
        self.current_scope
    }

	pub fn push(&mut self, scope: &str) -> Handle
	{
        assert!(self.current_scope!=INVALID_HANDLE);

        // Find if the resulting qualified namespace already exists.
        let current = self.get_path(self.get_current());
        if current.len() == 0
        {
            // Nothing in the current path.
        }
        else
        {

        }

        let handle = self.add(scope);
        handle
	}

    fn add(&mut self, scope: &str) -> Handle
    {
        let result = self.scope_arena.len();
        self.scope_arena.push(ScopeEntry::new(scope));
        result
    }

    fn size(&self) -> usize
    {
        self.scope_arena.len() as Handle
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
        if handle==INVALID_HANDLE
        {
            return result;
        }
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

#[cfg(test)]
mod tests
{
    use gen::scope::*;

    #[test]
    fn test_scopes_basic()
    {
        let cpf_name = "CPF";
        let gom_name = "GOM";
        let plugin_name = "Plugin";

        let mut scopes = Scopes::new();
        println!("***************************");
        println!("Current: {:?}", scopes.get_path(scopes.get_current()));

        // Add cpf.
        scopes.push(cpf_name);
        println!("Current: {:?}", scopes.get_path(scopes.get_current()));

        println!("***************************");
    }
}

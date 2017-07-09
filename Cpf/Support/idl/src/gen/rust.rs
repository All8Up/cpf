use std::usize;
use ast::*;
use gen::code_gen::CodeGenerator;


// ------------------------
type Handle = usize;
const INVALID_HANDLE: usize = usize::MAX;


// ------------------------
struct Namespace(String);

impl Namespace
{
	fn new(name: &str) -> Namespace
	{
		Namespace(name.to_string())
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
struct NamespaceEntry
{
	namespace: Namespace,
	children: Vec<usize>,
	parent: usize
}

impl NamespaceEntry
{
	fn new(name: &str) -> NamespaceEntry
	{
		NamespaceEntry {namespace: Namespace::new(name), children: vec![], parent: INVALID_HANDLE}
	}
}


// ------------------------
struct Namespaces
{
	namespace_arena: Vec<NamespaceEntry>,
	root: Handle
}

impl Namespaces
{
	fn new() -> Namespaces
	{
		Namespaces
		{
			namespace_arena: vec![NamespaceEntry::new("")],
			root: INVALID_HANDLE
		}
	}

	fn find(&self, namespace: Namespace) -> Handle
	{
		INVALID_HANDLE
	}

	fn get_name(&self, handle: Handle) -> &Namespace
	{
		return &self.namespace_arena[handle].namespace;
	}

	fn get_namespace(&self, handle: Handle) -> Namespace
	{
		let mut result = Namespace::new("");
		let path = self.get_path(handle);
		for element in path
		{
			result.append(&self.namespace_arena[element].namespace.0);
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
			let parent = self.namespace_arena[current].parent;
			if parent == INVALID_HANDLE
			{
				return result;
			}
			result.insert(0, parent);
			current = parent;
		}
	}
}


// ------------------------
pub struct Generator
{
	tree: ASTRef,
	namespaces: Namespaces,
	current_scope: usize
}

impl CodeGenerator for Generator
{
	fn generate(&mut self, tree: ASTRef, output: &str)
	{
		println!("Generating rust code to: {}", output);
		self.traverse(tree.clone(), |_, _| -> () {});
		self.tree = tree;
	}
}

impl Generator
{
	pub fn new() -> Generator
	{
		Generator
		{
			tree: NodeRef::new(Box::new(Comment {content: "".to_string()})),
			namespaces: Namespaces::new(),
			current_scope: 0
		}
	}

	fn traverse<T>(&mut self, tree: ASTRef, child_handler: T)
		where T: Fn(&mut Generator, ASTRef)
	{
		let mut current = tree;
		loop
		{
			// 1. Do something with the current node.
			if !self.handle(current.clone())
			{
				// Error, do something with this here.
				return
			}

			// 2. Walk through children.
			child_handler(self, current.clone());	

			// 3. Move to next sibling, exit if no sibling.
			match current.next_sibling()
			{
				None => return,
				Some(sibling) => current = sibling
			}
		}
	}

	fn handle(&mut self, node: ASTRef) -> bool
	{
		/*
		match *node.borrow()
		{
			Data::Block => println!("*** Data block"),
			Data::Module => println!("*** Module"),
			Data::Import {ref name} => println!("*** Import: {:?}", name),
			Data::Namespace {ref name} => {self.handle_namespace(node.clone(), name.to_string()); ()},
			Data::Interface {ref name, ref base} => println!("*** Interface: {:?} - {:?}", name, base),
			Data::FwdInterface {ref name} => println!("*** Forward Interface: {:?}", name),
		    Data::FwdStruct {ref name} => println!("*** Forward Struct: {:?}", name),
			Data::ClassID {ref name, ref cid} => println!("*** ClassID: {:?} - {:?}", name, cid),
			Data::InterfaceID {ref name, ref iid} => println!("*** InterfaceID: {:?} - {:?}", name, iid),
		    Data::ParamDecl {ref name, ref type_decl} => println!("*** ParamDecl: {:?} - {:?}", name, type_decl),
		    Data::MemberSignature {ref name, ref result_type} => println!("*** Member Signature: {:?} - {:?}", name, result_type),
		    Data::UnsignedConst {ref name, ref value} => println!("*** Unsigned Const: {:?} - {:?}", name, value),
		    Data::SignedConst {ref name, ref value} => println!("*** Signed Const: {:?} - {:?}", name, value),
		    Data::FloatConst {ref name, ref value} => println!("*** Float Const: {:?} - {:?}", name, value),
		    Data::ResultConst {ref name, ref is_error, ref sub_system, ref code} =>
		    	println!("*** Result Const: {:?} - {:?} - {:?} - {:?}", name, is_error, sub_system, code),
		    Data::Comment {ref content} => println!("*** Comment: {:?}", content),
//			_ => ()
		}
		*/

		true
	}

	fn handle_namespace(&mut self, node: ASTRef, name: String) -> bool
	{
		println!("*** Namespace: {:?}", name);
		for child in node.children()
		{
			self.handle_namespace_child(child);
		}
		true
	}

	fn handle_namespace_child(&mut self, node: ASTRef)
	{
//		println!("Child: {:?}", node);
	}
}

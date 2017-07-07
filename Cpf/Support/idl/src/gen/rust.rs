use ast::*;
use gen::code_gen::CodeGenerator;

pub struct Generator
{
	tree: NodeRef<Data>
}

impl CodeGenerator for Generator
{
	fn generate(&mut self, tree: NodeRef<Data>, output: &str)
	{
		println!("Generating rust code to: {}", output);
//		display_ast(tree.clone());
		self.traverse(tree.clone());
		self.tree = tree;
	}
}

impl Generator
{
	pub fn new() -> Generator
	{
		Generator {tree: NodeRef::new(Data::Block)}
	}

	fn traverse(&mut self, tree: NodeRef<Data>)
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
			match current.first_child()
			{
				None => (),
				Some(child) => self.traverse(child)
			}

			// 3. Move to next sibling, exit if no sibling.
			match current.next_sibling()
			{
				None => return,
				Some(sibling) => current = sibling
			}
		}
	}

	fn handle(&mut self, node: NodeRef<Data>) -> bool
	{
		match *node.borrow()
		{
			Data::Block => println!("*** Data block"),
			Data::Module => println!("*** Module"),
			Data::Import {ref name} => println!("*** Import: {:?}", name),
			Data::Namespace {ref name} => println!("*** Namespace: {:?}", name),
			Data::Interface {ref name, ref base} => println!("*** Interface: {:?} - {:?}", name, base),
			Data::FwdInterface {ref name} => println!("*** Forward Interface: {:?}", name),
		    Data::FwdStruct {ref name} => println!("*** Forward Struct: {:?}", name),
			Data::ClassID {ref name, ref cid} => println!("*** ClassID: {:?} - {:?}", name, cid),
			Data::InterfaceID {ref name, ref iid} => println!("*** InterfaceID: {:?} - {:?}", name, iid),
		    Data::ParamDecl {ref name, ref type_decl} => println!("*** ParamDecl: {:?} - {:?}", name, type_decl),
		    Data::MemberSignature {ref name, ref result_type} => println!("*** Member Signature: {:?} - {:?}", name, result_type),
			/*
		    Data::UnsignedConst(data) => println!("*** Unsigned Const"),
		    Data::SignedConst(data) => println!("*** Signed Const"),
		    Data::FloatConst(data) => println!("*** Float Const"),
		    Data::ResultConst(data) => println!("*** Result Const"),
		    Data::Comment(data) => println!("*** Comment"),
		    */
			_ => ()
		}
		true
	}
}

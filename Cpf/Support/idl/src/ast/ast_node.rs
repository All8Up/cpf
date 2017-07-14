use ast::*;
use gen::*;


/*
*/
pub type ASTRef = NodeRef<Box<ASTNode>>;

pub trait ASTNode
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool;
}

// ---------------
#[derive(Debug)]
pub struct Import
{
	pub name: String
}
impl ASTNode for Import
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
		generator.handle_import(self, node)
	}
}

// ---------------
#[derive(Debug)]
pub struct Namespace
{
	pub name: String
}
impl ASTNode for Namespace
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
        // Push in the new scope.
        generator.push_scope(&self.name);

        // Handle children.
        for child in node.children()
        {
            child.borrow().handle(generator, child.clone());
        }

        // Return to prior scope.
        generator.pop_scope();

		true
	}
}

// ---------------
#[derive(Debug)]
pub struct Interface
{
	pub name: String,
	pub base: Option<String>,
	pub statements: InterfaceStatements
}

impl ASTNode for Interface
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
        return generator.handle_interface(self, node.clone());
	}
}

// ---------------
#[derive(Debug)] pub struct FwdInterface {pub name: String}
impl ASTNode for FwdInterface {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct FwdStruct {pub name: String}
impl ASTNode for FwdStruct {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct ClassID {pub name: String, pub cid: String}
impl ASTNode for ClassID {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)]
pub struct InterfaceID
{
	pub name: String,
	pub iid: String
}
impl ASTNode for InterfaceID
{
	fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool
	{
		true
	}
}


// ---------------
#[derive(Debug)]
pub struct MethodSignature
{
	pub name: String,
	pub result_type: ModifiedType,
	pub parameters: ParameterList
}
impl ASTNode for MethodSignature
{
	fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool
	{
		println!("Signature: {:?}", self);
		true
	}
}

// ---------------
#[derive(Debug)] pub struct UnsignedConst {pub name: String, pub value: u64}
impl ASTNode for UnsignedConst {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct SignedConst {pub name: String, pub value: i64}
impl ASTNode for SignedConst {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct FloatConst {pub name: String, pub value: f64}
impl ASTNode for FloatConst {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct ConstResult
{
	pub name: String,
	pub is_error: bool,
	pub sub_system: String,
	pub code: String
}
impl ASTNode for ConstResult
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
		generator.handle_const_result(self, node)
	}
}

// ---------------
#[derive(Debug)] pub struct Comment {pub content: String}
impl ASTNode for Comment {fn handle(&self, _: &mut CodeGenerator, _: ASTRef) -> bool {true}}

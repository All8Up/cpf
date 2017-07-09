use ast::tree::*;
use ast::data_types::*;

pub type ASTRef = NodeRef<Box<ASTNode>>;

/*
*/
trait ASTNode
{
	fn handle(&self, node: ASTRef);
}

// ---------------
#[derive(Debug)] pub struct Import {pub name: String}
#[derive(Debug)] pub struct Namespace {pub name: String}
#[derive(Debug)] pub struct Interface {pub name: String, pub base: Option<String>}
#[derive(Debug)] pub struct FwdInterface {pub name: String}
#[derive(Debug)] pub struct FwdStruct {pub name: String}
#[derive(Debug)] pub struct ClassID {pub name: String, pub cid: String}
#[derive(Debug)] pub struct InterfaceID {pub name: String, pub iid: String}
#[derive(Debug)] pub struct ParamDecl {pub name: Option<String>, pub type_decl: TypeDecl}
#[derive(Debug)] pub struct MemberSignature {pub name: String, pub result_type: ModifiedType}
#[derive(Debug)] pub struct UnsignedConst {pub name: String, pub value: u64}
#[derive(Debug)] pub struct SignedConst {pub name: String, pub value: i64}
#[derive(Debug)] pub struct FloatConst {pub name: String, pub value: f64}
#[derive(Debug)] pub struct ResultConst {pub name: String, pub is_error: bool, pub sub_system: u16, pub code: u16}
#[derive(Debug)] pub struct Comment {pub content: String}

// ---------------
impl ASTNode for Import {fn handle(&self, node: ASTRef) {}}
impl ASTNode for Namespace {fn handle(&self, node: ASTRef) {}}
impl ASTNode for Interface {fn handle(&self, node: ASTRef) {}}
impl ASTNode for FwdInterface {fn handle(&self, node: ASTRef) {}}
impl ASTNode for FwdStruct {fn handle(&self, node: ASTRef) {}}
impl ASTNode for ClassID {fn handle(&self, node: ASTRef) {}}
impl ASTNode for InterfaceID {fn handle(&self, node: ASTRef) {}}
impl ASTNode for ParamDecl {fn handle(&self, node: ASTRef) {}}
impl ASTNode for MemberSignature {fn handle(&self, node: ASTRef) {}}
impl ASTNode for UnsignedConst {fn handle(&self, node: ASTRef) {}}
impl ASTNode for SignedConst {fn handle(&self, node: ASTRef) {}}
impl ASTNode for FloatConst {fn handle(&self, node: ASTRef) {}}
impl ASTNode for ResultConst {fn handle(&self, node: ASTRef) {}}
impl ASTNode for Comment {fn handle(&self, node: ASTRef) {}}

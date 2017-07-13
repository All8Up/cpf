use ast::*;
use gen::*;


/*
Non-node types.
*/
#[derive(Clone, Debug)]
pub struct Parameter
{
	pub name: String,
	pub data_type: TypeDecl
}

pub type ParameterList = Vec<Parameter>;

#[derive(Clone, Debug)]
pub enum InterfaceStatement
{
	IID
	{
		value: String
	},
	Method
	{
		name: String,
		result_type: ModifiedType,
		parameters: ParameterList
	}
}

pub type InterfaceStatements = Vec<InterfaceStatement>;

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
		true
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
		}
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
		// 	Load: extern fn(registry: *const iRegistry, name: *const c_char),
		generator.string_out("");
		generator.indent_out(&format!("pub struct {}_Vtbl", self.name));
		generator.indent_out("{");
		generator.indent();
		for stmt in self.statements.iter()
		{
			match stmt
			{
				&InterfaceStatement::IID {value: ref v} =>
					generator.indent_out(&format!("iid: {}", v)),
				&InterfaceStatement::Method {name: ref n, result_type: ref rt, parameters: ref p} =>
				{
					let mut params : String = "".to_string();
					for param in p
					{
						if !params.is_empty()
						{
							params += ", ";
						}
						params += &param.name;
						params += ": ";

						let dt = match param.data_type.data_type.data_type
						{
						    DataType::U8 => "uint8_t".to_string(),
						    DataType::I8 => "int8_t".to_string(),
						    DataType::U16 => "uint16_t".to_string(),
						    DataType::I16 => "int16_t".to_string(),
						    DataType::U32 => "uint32_t".to_string(),
						    DataType::I32 => "int32_t".to_string(),
						    DataType::U64 => "uint64_t".to_string(),
						    DataType::I64 => "int64_t".to_string(),
						    DataType::F32 => "c_float".to_string(),
						    DataType::F64 => "c_double".to_string(),
						    DataType::Char => "c_char".to_string(),
						    DataType::WChar => "wchar_t".to_string(),
						    DataType::Void => "void".to_string(),
						    DataType::SizeT => "size_t".to_string(),
						    DataType::Result => "uint32_t".to_string(),
						    DataType::NamedType {name: ref name} => " -> ".to_string() + &name
						};
						params += &dt;
					}

					let mut result = match rt.data_type
					{
					    DataType::U8 => " -> uint8_t".to_string(),
					    DataType::I8 => " -> int8_t".to_string(),
					    DataType::U16 => " -> uint16_t".to_string(),
					    DataType::I16 => " -> int16_t".to_string(),
					    DataType::U32 => " -> uint32_t".to_string(),
					    DataType::I32 => " -> int32_t".to_string(),
					    DataType::U64 => " -> uint64_t".to_string(),
					    DataType::I64 => " -> int64_t".to_string(),
					    DataType::F32 => " -> c_float".to_string(),
					    DataType::F64 => " -> c_double".to_string(),
					    DataType::Char => " -> c_char".to_string(),
					    DataType::WChar => " -> wchar_t".to_string(),
					    DataType::Void => "".to_string(),
					    DataType::SizeT => " -> size_t".to_string(),
					    DataType::Result => " -> uint32_t".to_string(),
					    DataType::NamedType {name: ref name} => " -> ".to_string() + &name
					};
					generator.indent_out(&format!("{}: extern fn({}){},", n, params, result));
				}
			}
		}
		generator.unindent();
		generator.indent_out("}");

		true
	}
}

// ---------------
#[derive(Debug)] pub struct FwdInterface {pub name: String}
impl ASTNode for FwdInterface {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct FwdStruct {pub name: String}
impl ASTNode for FwdStruct {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct ClassID {pub name: String, pub cid: String}
impl ASTNode for ClassID {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)]
pub struct InterfaceID
{
	pub name: String,
	pub iid: String
}
impl ASTNode for InterfaceID
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
		true
	}
}

// ---------------
#[derive(Debug)]
pub struct ParamDecl
{
	pub name: Option<String>,
	pub type_decl: TypeDecl
}
impl ASTNode for ParamDecl
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
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
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
		println!("Signature: {:?}", self);
		true
	}
}

// ---------------
#[derive(Debug)] pub struct UnsignedConst {pub name: String, pub value: u64}
impl ASTNode for UnsignedConst {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct SignedConst {pub name: String, pub value: i64}
impl ASTNode for SignedConst {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct FloatConst {pub name: String, pub value: f64}
impl ASTNode for FloatConst {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

// ---------------
#[derive(Debug)] pub struct ResultConst
{
	pub name: String,
	pub is_error: bool,
	pub sub_system: String,
	pub code: String
}
impl ASTNode for ResultConst
{
	fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool
	{
		generator.add_result(&self.name, self.is_error, &self.sub_system, &self.code)
	}
}

// ---------------
#[derive(Debug)] pub struct Comment {pub content: String}
impl ASTNode for Comment {fn handle(&self, generator: &mut CodeGenerator, node: ASTRef) -> bool {true}}

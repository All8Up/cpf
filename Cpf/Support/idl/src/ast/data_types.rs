use ast::annotation::*;

#[derive(Clone, Debug)]
pub enum TypeQualifier
{
    Const
}

#[derive(Clone, PartialEq, Debug)]
pub enum DataType
{
    U8,
    I8,
    U16,
    I16,
    U32,
    I32,
    U64,
    I64,
    F32,
    F64,
    Char,
    WChar,
    Void,
    SizeT,
    Result,
    NamedType {name: String}
}

impl ToString for DataType
{
    fn to_string(&self) -> String
    {
        return match self
            {
                &DataType::U8 => "uint8_t".to_string(),
                &DataType::I8 => "int8_t".to_string(),
                &DataType::U16 => "uint16_t".to_string(),
                &DataType::I16 => "int16_t".to_string(),
                &DataType::U32 => "u32".to_string(),
                &DataType::I32 => "i32".to_string(),
                &DataType::U64 => "u64".to_string(),
                &DataType::I64 => "i64".to_string(),
                &DataType::F32 => "f32".to_string(),
                &DataType::F64 => "f64".to_string(),
                &DataType::Char => "c_char".to_string(),
                &DataType::WChar => "wchar_t".to_string(),
                &DataType::Void => "void".to_string(),
                &DataType::SizeT => "size_t".to_string(),
                &DataType::Result => "u32".to_string(),
                &DataType::NamedType { ref name } => " -> ".to_string() + &name
            }
    }
}

#[derive(Clone, Debug)]
pub struct ModifiedType
{
    pub qualifier: Option<TypeQualifier>,
    pub data_type: DataType,
    pub indirection_count: u32
}

#[derive(Clone, Debug)]
pub struct TypeDecl
{
    pub annotation: Option<Annotation>,
    pub data_type: ModifiedType
}

pub use ast::*;

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

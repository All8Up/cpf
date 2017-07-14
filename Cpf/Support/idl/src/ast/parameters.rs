use ast::*;

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

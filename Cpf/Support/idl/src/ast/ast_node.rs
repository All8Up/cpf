use ast::data_types::*;

#[derive(Debug)]
pub enum Data
{
	Block,
	Module,
	Import {name: String},
	Namespace {name: String},
	Interface {name: String, base: Option<String>},
	FwdInterface {name: String},
    FwdStruct {name: String},
	ClassID {name: String, cid: String},
	InterfaceID {name: String, iid: String},
    ParamDecl {name: Option<String>, type_decl: TypeDecl},
    MemberSignature {name: String, result_type: ModifiedType},
    UnsignedConst {name: String, value: u64},
    Signedconst {name: String, value: i64},
    FloatConst {name: String, value: f64},
    ResultConst {name: String, is_error: bool, sub_system: u16, code: u16}
}

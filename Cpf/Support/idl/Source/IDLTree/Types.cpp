//////////////////////////////////////////////////////////////////////////
#include "IDLTree/Types.hpp"

using namespace IDLTree;

std::string IDLTree::TypeString(AllTypes type)
{
	std::string result;
	switch (type)
	{
	case AllTypes::Unknown:		result = "Unknown"; break;
	case AllTypes::U8:			result = "U8"; break;
	case AllTypes::S8:			result = "S8"; break;
	case AllTypes::U16:			result = "U16"; break;
	case AllTypes::S16:			result = "S16"; break;
	case AllTypes::U32:			result = "U32"; break;
	case AllTypes::S32:			result = "S32"; break;
	case AllTypes::U64:			result = "U64"; break;
	case AllTypes::S64:			result = "S64"; break;
	case AllTypes::F32:			result = "f32"; break;
	case AllTypes::F64:			result = "f32"; break;
	case AllTypes::Void:		result = "void"; break;
	case AllTypes::Result:		result = "result"; break;
	case AllTypes::Identifier:	result = "symbol"; break;
	}
	return result;
}

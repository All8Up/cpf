//////////////////////////////////////////////////////////////////////////
#include "AST/Types.hpp"

using namespace AST;

std::string AST::TypeString(IntegralType type)
{
	std::string result;
	switch (type)
	{
	case IntegralType::Unknown:	result = "Unknown"; break;
	case IntegralType::U8:		result = "U8"; break;
	case IntegralType::S8:		result = "S8"; break;
	case IntegralType::U16:		result = "U16"; break;
	case IntegralType::S16:		result = "S16"; break;
	case IntegralType::U32:		result = "U32"; break;
	case IntegralType::S32:		result = "S32"; break;
	case IntegralType::U64:		result = "U64"; break;
	case IntegralType::S64:		result = "S64"; break;
	}
	return result;
}

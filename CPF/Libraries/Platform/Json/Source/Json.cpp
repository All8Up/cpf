#include "Json/Json.hpp"
#include "rapidjson/document.h"

using namespace Cpf;
using namespace Platform;

#define DOC (*reinterpret_cast<rapidjson::Document*>(mpDocument))

Json::Json()
	: mpDocument(new rapidjson::Document)
{
}


Json::~Json()
{
	delete reinterpret_cast<rapidjson::Document*>(mpDocument);
}


bool Json::Parse(const char* json)
{
	DOC.Parse(json);
	if (DOC.HasParseError())
		return false;
	return true;
}

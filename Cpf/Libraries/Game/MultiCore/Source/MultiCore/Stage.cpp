//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Stage.hpp"
#include "MultiCore/Service.hpp"
#include "Hash/Crc.hpp"

using namespace Cpf;
using namespace MultiCore;

Stage::Stage(Service* service, const String& name, const Dependencies& dependencies)
	: mpService(service)
	, mName(name)
	, mID(Platform::Hash::ComputeCrc64(name.c_str(), name.size(), uint64_t(-1)))
	, mDependencies(dependencies)
{
	
}

Stage::~Stage()
{}

Service* Stage::GetService() const
{
	return mpService;
}

StageID Stage::GetID() const
{
	return mID;
}

const String& Stage::GetName() const
{
	return mName;
}

const Stage::Dependencies& Stage::GetDependencies() const
{
	return mDependencies;
}

//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

CPF_EXPORT_RESOURCES Monitor* FileSystem::Create()
{
	return new FileSystem();
}

bool FileSystem::Touch(ID id)
{
	(void)id;
	return false;
}

void FileSystem::TouchAll()
{}

FileSystem::FileSystem()
{}

FileSystem::~FileSystem()
{}

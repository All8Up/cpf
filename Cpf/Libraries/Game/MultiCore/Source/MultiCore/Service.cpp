//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Service.hpp"

using namespace Cpf;
using namespace MultiCore;

Service::Service(ServiceID id)
	: mID(id)
{}

Service::~Service()
{}

ServiceID Service::GetID() const
{
	return mID;
}

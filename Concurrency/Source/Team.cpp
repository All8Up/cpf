#include "Concurrency/Team.hpp"

using namespace Cpf;
using namespace Concurrency;


Service::~Service()
{}


//////////////////////////////////////////////////////////////////////////
bool ServiceFactory::Install(const ServiceDesc& desc)
{
	if (mServiceMap.find(desc.Name) != mServiceMap.end())
	{
		CPF_LOG(Concurrency, Error) << "Duplicate service installation: " << desc.Name;
		return false;
	}

	mServiceMap[desc.Name] = &desc;
	CPF_LOG(Concurrency, Info) << "Installed service: " << desc.Name;

	return true;
}

bool ServiceFactory::Remove(const ServiceDesc& desc)
{
	auto it = mServiceMap.find(desc.Name);
	if (it != mServiceMap.end())
	{
		CPF_LOG(Concurrency, Info) << "Removed service: " << desc.Name;
		mServiceMap.erase(it);
		return true;
	}

	CPF_LOG(Concurrency, Error) << "Removal of unknown service: " << desc.Name;
	return false;
}

Service* ServiceFactory::Create(const ServiceDesc& desc) const
{
	auto it = mServiceMap.find(desc.Name);
	if (it != mServiceMap.end())
	{
		if (it->second->Create)
		{
			CPF_LOG(Concurrency, Info) << "Creating service: " << desc.Name;
			return (*it->second->Create)();
		}
		CPF_LOG(Concurrency, Info) << "No creator for service: " << desc.Name;
		return nullptr;
	}

	CPF_LOG(Concurrency, Error) << "Attempt to create non-installed service: " << desc.Name;
	return nullptr;
}

Service* ServiceFactory::Create(const String& name) const
{
	auto it = mServiceMap.find(name);
	if (it != mServiceMap.end())
	{
		if (it->second->Create)
		{
			CPF_LOG(Concurrency, Info) << "Creating service: " << name;
			return (*it->second->Create)();
		}
		CPF_LOG(Concurrency, Info) << "No creator for service: " << name;
		return nullptr;
	}

	CPF_LOG(Concurrency, Error) << "Attempt to create non-installed service: " << name;
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
Team::Team(Scheduler& scheduler)
: mScheduler(scheduler)
, mQueue(Move(scheduler.CreateQueue()))
{}

Team::~Team()
{}

bool Team::Dependency(String serviceInstance, String serviceStage, const Vector<StageDep>& depends)
{
	StageRef stageRef = {serviceInstance, serviceStage};
	auto it = mStageDeps.find(stageRef);
	if (it != mStageDeps.end())
	{
		it->second.insert(it->second.begin(), depends.begin(), depends.end());
		return true;
	}
	else
		mStageDeps[stageRef] = depends;
	return false;
}

bool Team::Resolve()
{
	return _InitializeServices() && _BuildStageList();
}

bool Team::_InitializeServices()
{
	while (!mInstances.empty())
	{
		bool initedOne = false;
		for (const auto& it : mInstances)
		{
			Vector<Service*> initList;
			// Find any references needed to initialize a service.
			if (!it.second.second.empty())
			{
				const Vector<String>& names = it.second.second;
				for (const auto& name : names)
				{
					auto service = Find(name);
					if (service)
						initList.push_back(service);
					else
						continue;
				}
			}
			// Attempt to initialize the service.  This can still fail
			// if the service decides to lookup another service dynamically
			// instead of using the initializer lists and that other service
			// is not initialized yet.  Eventually, everything should resolve
			// as long as there are no circular dependencies.
			if (it.second.first->Initialize(initList))
			{
				CPF_LOG(Concurrency, Info) << "Resolved: " << it.first;
				mResolvedInstances[it.first] = it.second.first;
				mInstances.erase(it.first);
				// Keep on initializing.
				initedOne = true;
				break;
			}
		}

		// If we went through the list and were unable to initialize anything,
		// we have a circular dependency and need to bail out in error.
		if (initedOne)
			continue;

		CPF_LOG(Concurrency, Error) << "Failed to resolve services, likely a circular dependency is defined.";
		break;
	}
	return mInstances.empty();
}

bool Team::_BuildStageList()
{
	// Build the service defined stage list and internal dependencies.
	for (const auto& it : mResolvedInstances)
	{
		const auto& desc = it.second->GetDesc();
		for (const auto& stage : desc.Stages)
		{
			StageRef stageRef = {it.first, stage.mName};
			mStageMap[stageRef] = stage.mDeps;
		}
	}

	// Add the end user defined dependencies.
	for (const auto& it : mStageDeps)
	{
		const auto& stage = mStageMap.find(it.first);
		if (stage != mStageMap.end())
		{
			stage->second.insert(stage->second.end(), it.second.begin(), it.second.end());
		}
		else
		{
			CPF_LOG(Concurrency, Error) << "Dependency definition not resolved: " << it.first.first << " : " << it.first.second;
			return false;
		}
	}

	// TODO: Testing code.
	CPF_LOG(Concurrency, Info) << "Stage List:";
	for (const auto& it : mStageMap)
	{
		CPF_LOG(Concurrency, Info) << "  " << it.first.first << " : " << it.first.second;
	}
	CPF_LOG(Concurrency, Info) << "--------------------------------------------";

	// Find the root stage, should be the only stage with no dependencies.
	// If there are multiple stages with no dependencies the last one found
	// (no guaranteed order) will be used as the root.
	for (const auto& it : mStageMap)
	{
		if (it.second.empty())
		{
			CPF_LOG(Concurrency, Info) << "Root= " << it.first.first << " : " << it.first.second;
			mStages.push_back(it.first);
		}
	}
	// Remove the stages that are roots.
	for (const auto& it : mStages)
		mStageMap.erase(mStageMap.find(it));

	CPF_LOG(Concurrency, Info) << "--------------------------------------------";
	CPF_LOG(Concurrency, Info) << "Sorted stages:";
	for (const auto& it : mStages)
	{
		CPF_LOG(Concurrency, Info) << "  " << it.first << " : " << it.second;
	}

	return true;
}

void Team::Shutdown()
{}

bool Team::Instance(const String& instanceName, const String& factoryName, const Vector<String>& inits)
{
	Service* service = mServices.Create(factoryName);
	if (service)
	{
		CPF_LOG(Concurrency, Info) << "Added instance of: " << factoryName << ". As: " << instanceName;
		mInstances[instanceName] = { service, inits };
		return true;
	}
	return false;
}

Service* Team::Find(const String& name)
{
	auto it = mResolvedInstances.find(name);
	if (it == mResolvedInstances.end())
		return nullptr;
	return it->second;
}

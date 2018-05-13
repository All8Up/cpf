//////////////////////////////////////////////////////////////////////////
#include "LoadBalancer.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Platform;
using namespace Threading;

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction.
LoadBalanceMinimize::LoadBalanceMinimize(Plugin::iRegistry* registry, iUnknown*)
	: mpRegistry(registry)
    , mMaxUsableThreads(Thread::GetHardwareThreadCount())
{
}

//////////////////////////////////////////////////////////////////////////
// iThreadController implementations.

int32_t CPF_STDCALL LoadBalanceMinimize::GetMaxThreads()
{
    return mMaxUsableThreads;
}

GOM::Result CPF_STDCALL LoadBalanceMinimize::SetMaxThreads(int32_t count)
{
    mMaxUsableThreads = count;
    return GOM::kOK;
}

int32_t CPF_STDCALL LoadBalanceMinimize::GetActiveThreads()
{
    int32_t result = 0;
    for (auto& controller : mControllers)
        result += controller->GetActiveThreads();
    return result;
}

void CPF_STDCALL LoadBalanceMinimize::SetActiveThreads(int32_t count)
{ (void)count; }

void CPF_STDCALL LoadBalanceMinimize::SetPriority(SchedulingPriority level)
{
    for (auto& controller : mControllers)
        controller->SetPriority(level);
}

SchedulingPriority CPF_STDCALL LoadBalanceMinimize::GetPriority()
{
    if (!mControllers.empty())
        return mControllers[0]->GetPriority();
    return SchedulingPriority::eNormal;
}

float CPF_STDCALL LoadBalanceMinimize::GetUtilization()
{
    float result = 0.0f;
    for (const auto& controller : mControllers)
        result += controller->GetUtilization();
    return result;
}

void CPF_STDCALL LoadBalanceMinimize::GetThreadTimeInfo(ThreadTimeInfo* timeInfo) { (void)timeInfo; }

int32_t CPF_STDCALL LoadBalanceMinimize::GetDesiredThreadCount()
{
    int32_t result = 0;
    for (const auto& controller : mControllers)
        result += controller->GetDesiredThreadCount();
    return result;
}


//////////////////////////////////////////////////////////////////////////
// iLoadBalancer implementations.

GOM::Result CPF_STDCALL LoadBalanceMinimize::SetControllers(int32_t count, iThreadController** controllers)
{
    if (controllers)
    {
        // Move the pointers to a temporary just in case we are the only one maintaining references
        // and it would be destroyed while the new list is built.
        auto oldControllers = STD::Move(mControllers);
        for (int i = 0; i < count; ++i)
        {
            mControllers.push_back(IntrusivePtr<iThreadController>(controllers[i]));
        }

        return GOM::kOK;
    }

    return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL LoadBalanceMinimize::GetControllers(int32_t* count, iThreadController** controllers)
{
    if (count)
    {
        if (controllers)
        {
            int32_t i = 0;
            for (const auto& controller : mControllers)
                controllers[i++] = controller;
        }
        else
            *count = int32_t(mControllers.size());
        return GOM::kOK;
    }

    return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL LoadBalanceMinimize::RebalanceThreads()
{
    STD::Vector<int32_t> targets(mControllers.size());
    int32_t i = 0;
    int32_t total = 0;
    for (auto& controller : mControllers)
    {
        targets[i] = controller->GetDesiredThreadCount();
        total += targets[i++];
    }
    // Proportionally reduce threads to fit into max.
    if (total > mMaxUsableThreads)
    {
        // TODO: Decide how best to approach this.
    }

    // Apply the new balance.
    i = 0;
    for (auto& controller : mControllers)
    {
        controller->SetActiveThreads(targets[i++]);
    }

    return GOM::kOK;
}

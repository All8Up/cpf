//////////////////////////////////////////////////////////////////////////
#include "Application/Application.hpp"
#include "Application/Arguments.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Logging/Logging.hpp"
#include "Memory/Memory.hpp"
#include "Threading.hpp"


//////////////////////////////////////////////////////////////////////////
class SchedulerPerformance : public Cpf::Application
{
public:
	CPF_ALIGNED_OBJECT(SchedulerPerformance);

	SchedulerPerformance();
	virtual ~SchedulerPerformance();

	virtual int Start(const Cpf::CommandLine&) override;

private:
	int64_t _InstructionRate(int threadCount);
	int64_t _BasicWork(int threadCount);
	int64_t _InstructionRateAlternatePassWait(int threadCount);

	Cpf::Concurrency::Scheduler m_Scheduler;
	Cpf::ScopedInitializer<Cpf::ThreadingInitializer> mLibInit;
};


//////////////////////////////////////////////////////////////////////////
SchedulerPerformance::SchedulerPerformance()
{
	Cpf::Threading::Thread::Group group(12);
	m_Scheduler.Initialize(std::move(group));
}

SchedulerPerformance::~SchedulerPerformance()
{
	m_Scheduler.Shutdown();
}


//////////////////////////////////////////////////////////////////////////
using namespace Cpf;
using namespace Platform;
using namespace Threading;
using namespace Concurrency;

int SchedulerPerformance::Start(const Cpf::CommandLine&)
{
	{
		int threadCounts[] = {
			1,
			2,
			6,
			8,
			12
		};

		// Run through a set of performance metric functions.
		struct MetricPair
		{
			std::string Name;
			std::string MetricName;
			std::function<int64_t(int)> Func;
		};
		std::vector<MetricPair> perfFunctions
		{
			{"Instruction rate", "Instructions", std::bind(&SchedulerPerformance::_InstructionRate, this, std::placeholders::_1)},
			{"Basic work", "Basic", std::bind(&SchedulerPerformance::_BasicWork, this, std::placeholders::_1)}
//			, {"Wait pass alternation", std::bind(&SchedulerPerformance::_InstructionRateAlternatePassWait, this, std::placeholders::_1)}
		};

		// Using a fixed set of thread counts, run the testing functionality.
		for (auto& metric : perfFunctions)
		{
			auto start = Time::Value::Now();

			for (int i = 0; i < sizeof(threadCounts) / sizeof(int); ++i)
			{
				// Run each test several times and take an average.
				static const int averageCount = 5;
				int64_t times[averageCount];
				for (int j = 0; j < averageCount; ++j)
					times[j] = metric.Func(threadCounts[i]);

				int64_t avgTime = 0;
				int64_t minTime = 10000000000;
				int64_t maxTime = 0;
				for (int k = 0; k < averageCount; ++k)
				{
					avgTime += times[k];
					minTime = std::min(times[k], minTime);
					maxTime = std::max(times[k], maxTime);
				}
				avgTime /= averageCount;
				std::cout << "##teamcity[buildStatisticValue key='ConcurrencySchedulerMin_" << threadCounts[i] << "' value='" << minTime << "']" << std::endl;
				std::cout << "##teamcity[buildStatisticValue key='ConcurrencySchedulerMax_" << threadCounts[i] << "' value='" << maxTime << "']" << std::endl;
				std::cout << "##teamcity[buildStatisticValue key='ConcurrencySchedulerAvg_" << threadCounts[i] << "' value='" << avgTime << "']" << std::endl;
			}

			//////////////////////////////////////////////////////////////////////////
			auto end = Time::Value::Now();
			auto deltaTime = end - start;

			// Report the total time to teamcity.  This is a primitive test for kpi's.
			std::cout << "##teamcity[buildStatisticValue key='ConcurrencySchedulerTotalTime_" << metric.MetricName << "' value='"
				<< int64_t(Time::Us(deltaTime)) << "']" << std::endl;
		}
	}
	return 0;
}


int64_t SchedulerPerformance::_InstructionRate(int threadCount)
{
	static const int loopCount = 5;
	static const int instructionCount = 500000;

	struct CPF_ALIGN(16) TestData
	{
		int32_t HitCount;
	};
	TestData* testData = new TestData;

	Scheduler::Queue instructions(instructionCount);
	for (int i = 0; i < instructionCount; ++i)
		instructions.All([](Scheduler::ThreadContext&, void* context)
	{
		(void)context;
	}, testData);

	m_Scheduler.SetActiveThreads(threadCount);
	Scheduler::Semaphore sync;
	auto start = Time::Value::Now();
	{
		for (int i = 0; i < loopCount; ++i)
		{
			m_Scheduler.Execute(instructions, false);
			m_Scheduler.Submit(sync);
			sync.Acquire();
		}
	}
	auto end = Time::Value::Now();
	auto delta = Time::Seconds(end - start);

	// Figure out the opcodes per second.
	int64_t opPerSecond(int64_t(instructionCount / float(delta)));
	std::cout << "##teamcity[buildStatisticValue key='ConcurrencyOpcodesPerSecond_" << threadCount << "' value='" << int64_t(opPerSecond) << "']" << std::endl;

	delete testData;
	return int64_t(Time::Us(end - start));
}


int64_t SchedulerPerformance::_BasicWork(int threadCount)
{
	static const int loopCount = 5;
	static const int instructionCount = 1000 * threadCount;
	static const auto innerLoopCount = 100;

	struct CPF_ALIGN(16) TestData
	{
		int32_t HitCount;
	};
	TestData* testData = new TestData;

	Scheduler::Queue instructions(instructionCount);
	for (int i = 0; i < instructionCount; ++i)
		instructions.All([](Scheduler::ThreadContext&, void* context)
	{
		(void)context;
		Cpf::Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
		int test[innerLoopCount];
		for (auto i = 0; i < innerLoopCount; ++i)
		{
			for (auto j = 0; j < innerLoopCount; ++j)
				test[j] = int(std::sqrt(j));
			for (auto j = 0; j < innerLoopCount; ++j)
				test[j] = int(std::pow(test[j], 2));
			for (auto j = 0; j < innerLoopCount; ++j)
				test[j] = int(std::sin(test[j]));
		}
	}, testData);

	m_Scheduler.SetActiveThreads(threadCount);
	Scheduler::Semaphore sync;
	auto start = Time::Value::Now();
	{
		Semaphore wait;
		for (int i = 0; i < loopCount; ++i)
		{
			m_Scheduler.Execute(instructions, false);
		}
		m_Scheduler.Submit(sync);
		sync.Acquire();
	}
	auto end = Time::Value::Now();
	auto delta = Time::Seconds(end - start);

	// Figure out the opcodes per second.
	int64_t opPerSecond(int64_t(instructionCount / float(delta)));
	std::cout << "##teamcity[buildStatisticValue key='ConcurrencyBasicWorkRate_" << threadCount << "' value='" << int64_t(opPerSecond) << "']" << std::endl;

	delete testData;
	return int64_t(Time::Us(end - start));
}


int64_t SchedulerPerformance::_InstructionRateAlternatePassWait(int threadCount)
{
	auto start = Time::Value::Now();
	m_Scheduler.SetActiveThreads(threadCount);
	{

	}
	auto end = Time::Value::Now();
	return int64_t(Time::Us(end - start));
}


//////////////////////////////////////////////////////////////////////////
CPF_CREATE_APPLICATION(SchedulerPerformance);

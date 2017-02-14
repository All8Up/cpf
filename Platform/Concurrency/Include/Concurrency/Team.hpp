//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "String.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Map.hpp"
#include "UnorderedMap.hpp"
#include "Logging/Logging.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		//////////////////////////////////////////////////////////////////////////
		enum class StageOrder : int32_t
		{
			eDuring,
			eAfter
		};

		//////////////////////////////////////////////////////////////////////////
		using StageRef = Pair<String, String>;
		using StageDep = Pair<StageOrder, StageRef>;
		struct StageDesc
		{
			using StageDeps = Vector<StageDep>;

			const char* mName;
			StageDeps mDeps;
		};

		//////////////////////////////////////////////////////////////////////////
		class Service;
		struct ServiceDesc
		{
			const char* Name;
			Vector<const char*> InitTypes;
			Vector<StageDesc> Stages;
			Service* (*Create)();
		};

		//////////////////////////////////////////////////////////////////////////
		class Service
		{
		public:
			virtual ~Service() = 0;

			virtual const ServiceDesc& GetDesc() const = 0;
			virtual bool Initialize(const Vector<Service*>& initList) = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		class ServiceFactory
		{
		public:
			bool Install(const ServiceDesc& desc);
			bool Remove(const ServiceDesc& desc);
			Service* Create(const ServiceDesc& desc) const;
			Service* Create(const String& name) const;

			template<typename TYPE>
			bool Install() { return Install(TYPE::Desc); }
			template<typename TYPE>
			bool Remove() { return Remove(TYPE::Desc); }
			template<typename TYPE>
			TYPE* Create() const { return Create(TYPE::Desc); }

		private:
			using ServiceMap = UnorderedMap<String, const ServiceDesc*>;

			ServiceMap mServiceMap;
		};

		//////////////////////////////////////////////////////////////////////////
		class Team
		{
		public:
			//
			Team(Scheduler& scheduler);
			~Team();

			//
			bool operator ()() { return false; }

			//
			bool Resolve();
			void Shutdown();

			//
			template<typename TYPE>
			bool Install() { return mServices.Install<TYPE>(); }

			bool Instance(const String& instanceName, const String& factoryName, const Vector<String>& inits = Vector<String>());
			bool Dependency(String, String, const Vector<StageDep>& depends);
			Service* Find(const String& name);

		private:
			//
			bool _InitializeServices();
			bool _BuildStageList();

			//
			Scheduler& mScheduler;
			Scheduler::Queue mQueue;
			ServiceFactory mServices;

			using InitService = Pair<Service*, Vector<String> >;
			UnorderedMap<String, InitService> mInstances;
			UnorderedMap<String, Service*> mResolvedInstances;
			Map<StageRef, Vector<StageDep>> mStageDeps;
			using StageMap = Map<StageRef, Vector<StageDep>>;
			StageMap mStageMap;
			Vector<StageRef> mStages;
		};
	}
}

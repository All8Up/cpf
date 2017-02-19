//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "RefCounted.hpp"
#include "Vector.hpp"
#include "Pair.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/ScopedLock.hpp"
#include "Concurrency/ThreadContext.hpp"
#include "MultiCore/Container.hpp"
#include "MultiCore/Partitioning.hpp"
#include "Tuple.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace GO
	{
		using ObjectID = int64_t;
		constexpr ObjectID kInvalidObjectID = int64_t(-1);
		constexpr ObjectID kTransientID = int64_t(0x0800000000000000);

		using ComponentID = int64_t;
		constexpr ComponentID kInvalidComponentID = int64_t(-1);

		using SystemID = int64_t;
		constexpr ComponentID kInvalidSystemID = int64_t(-1);

		class Object;
		class Component;
		class Service;
		class System;

		// Stages within the service are update loops.  They work in a similar fashion to
		// 3D pipeline stages though Stages can be merged and/or executed in parallel
		// when there are no direct conflicts in data descriptions.
		// TODO: Decide where to put this, may not want it in GO.
		// TODO: This is a really bad implementation which will be important to fix later.
		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			enum class Type : int32_t
			{
				eConcurrent,	// Can work with other stages.
				eIsolate		// Must run in isolation from other stages.
			};

			using Dependency = Pair<String, String>;	// Owning system name, Stage name.
			using Dependencies = Vector<Dependency>;
			using FuncType_t = void(*)(System*, Object*);

			Stage(System* system) : mpSystem(system) {}

			void AddUpdate(System* s, Object* o, FuncType_t f)
			{
				mWork.Acquire();
				mWork.Add({s, o, f});
				mWork.Release();
			}
			void RemoveUpdate(System* s, Object* o, FuncType_t f)
			{
				mWork.Acquire();
				mWork.Remove({s, o, f});
				mWork.Release();
			}

			static void Update(Concurrency::ThreadContext& tc, void* context)
			{
				Stage& self = *reinterpret_cast<Stage*>(context);
				MultiCore::EqualPartitions<MultiCore::VectorContainer<UpdateTuple_t>, Caller>::Execute(self.mWork, tc, &self.mCaller);
			}

			System* GetSystem() const { return mpSystem; }
			virtual bool ResolveDependencies(GO::Service*, GO::System*) { return true; }

		private:
			System* mpSystem;
			using UpdateTuple_t = Tuple<System*, Object*, FuncType_t>;
			MultiCore::VectorContainer<UpdateTuple_t> mWork;
			struct Caller
			{
				void Execute(const UpdateTuple_t& work)
				{
					(*std::get<2>(work))(std::get<0>(work), std::get<1>(work));
				}
			} mCaller;
		};
	}
}

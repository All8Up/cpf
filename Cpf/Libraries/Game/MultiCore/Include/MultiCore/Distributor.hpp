//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "Concurrency/ThreadContext.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/ScopedLock.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class DistributorBase
		{
		public:
			virtual ~DistributorBase() = 0;

			virtual void operator ()(Concurrency::ThreadContext&, void*) = 0;
		};

		class WorkContainerBase
		{
		public:
		};

		template<typename WORKTYPE>
		class VectorContainer : public WorkContainerBase
		{
		public:
			using WorkType = WORKTYPE;

			void Acquire() { mLock.Acquire(); }
			void Release() { mLock.Release(); }

			size_t GetSize() const { Platform::Threading::ScopedLock<Platform::Threading::Mutex> lock(mLock);  return mWork.size(); }
			void Clear() const { Platform::Threading::ScopedLock<Platform::Threading::Mutex> lock(mLock); mWork.clear(); }
			void Add(WorkType&& w) { Platform::Threading::ScopedLock<Platform::Threading::Mutex> lock(mLock); mWork.emplace_back(Move(w)); }
			void Remove(WorkType&& w);

		private:
			Platform::Threading::Mutex mLock;
			Vector<WorkType> mWork;
		};

		class EqualPartitioning
		{
		public:
			void operator ()(WorkContainerBase& container, Concurrency::ThreadContext& threadContext, void* context)
			{}
		};

		class SlicedPartitioning
		{
		public:
		};


		template<typename CONTAINER, typename PARTITIONING>
		class Distributor : public DistributorBase
		{
		public:
			using WorkType = typename CONTAINER::WorkType;

			~Distributor() override;

			void operator ()(Concurrency::ThreadContext&, void*);

			void Add(WorkType work);
			void Remove(WorkType work);

		private:
			CONTAINER mContainer;
			PARTITIONING mPartitioning;
		};

		template<typename CONTAINER, typename PARTITIONING>
		void Distributor<CONTAINER, PARTITIONING>::operator ()(Concurrency::ThreadContext& threadContext, void* context)
		{
			mPartitioning(mContainer, threadContext, context);
		}
	}
}

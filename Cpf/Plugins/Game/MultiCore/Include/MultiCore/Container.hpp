//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "Threading/Mutex.hpp"
#include "Functional.hpp"
#include "Vector.hpp"
#include "Concurrency/Concurrency.hpp"
#include "Move.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		//////////////////////////////////////////////////////////////////////////
		class ContainerBase
		{
		public:
			virtual ~ContainerBase() {}

			virtual void Begin() {}
			virtual void End() {}
		};

		//////////////////////////////////////////////////////////////////////////
		template<typename WORKTYPE>
		class VectorContainer : public ContainerBase
		{
		public:
			using WorkType = WORKTYPE;

			void Acquire();
			void Release();

			size_t GetSize() const;
			void Add(WorkType&& work);
			void Remove(const WorkType& work);

			const WorkType& operator [](const size_t index) const;

		private:
			Threading::Mutex mLock;
			Vector<WorkType> mWork;
		};


		//////////////////////////////////////////////////////////////////////////
		template<typename WORKTYPE>
		void VectorContainer<WORKTYPE>::Acquire()
		{
			mLock.Acquire();
		}

		template<typename WORKTYPE>
		void VectorContainer<WORKTYPE>::Release()
		{
			mLock.Release();
		}

		template<typename WORKTYPE>
		size_t VectorContainer<WORKTYPE>::GetSize() const
		{
			return mWork.size();
		}

		template<typename WORKTYPE>
		void VectorContainer<WORKTYPE>::Add(WorkType&& work)
		{
			mWork.emplace_back(Move(work));
		}

		template<typename WORKTYPE>
		void VectorContainer<WORKTYPE>::Remove(const WorkType& work)
		{
			for (auto ibegin = mWork.begin(), iend = mWork.end(); ibegin!=iend; ++ibegin)
			{
				if (*ibegin == work)
				{
					mWork.erase(ibegin);
					return;
				}
			}
			// Trying to erase something that does not exist.
			CPF_ASSERT_ALWAYS;
		}

		template<typename WORKTYPE>
		const typename VectorContainer<WORKTYPE>::WorkType& VectorContainer<WORKTYPE>::operator [](const size_t index) const
		{
			return mWork[index];
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename WORKTYPE, typename LESSTHAN = Less<WORKTYPE>>
		class SortedVectorContainer : public ContainerBase
		{
		public:
			using WorkType = WORKTYPE;

			void Acquire();
			void Release();

			size_t GetSize() const;
			void Add(WorkType&& work);
			void Remove(const WorkType& work);

			const WorkType& operator [](const size_t index) const;

			void Begin() override;
			void End() override;

		private:
			using WorkVector = Vector<WorkType>;

			int _Find(const WorkType& work) const;

			Threading::Mutex mLock;
			WorkVector mWork;

			// Per thread add/remove.
			WorkVector mAdditions[Concurrency::kMaxThreads];
			WorkVector mDeletions[Concurrency::kMaxThreads];
		};

		//////////////////////////////////////////////////////////////////////////
		template<typename WORKTYPE, typename LESSTHAN>
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::Acquire()
		{
			mLock.Acquire();
		}

		template<typename WORKTYPE, typename LESSTHAN>
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::Release()
		{
			mLock.Release();
		}

		template<typename WORKTYPE, typename LESSTHAN>
		size_t SortedVectorContainer<WORKTYPE, LESSTHAN>::GetSize() const
		{
			return mWork.size();
		}

		template<typename WORKTYPE, typename LESSTHAN>
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::Add(WorkType&& work)
		{
			mAdditions[0].emplace_back(Move(work));
		}

		template<typename WORKTYPE, typename LESSTHAN>
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::Remove(const WorkType& work)
		{
			auto it = _Find(work);
			CPF_ASSERT(it >= 0);
			CPF_ASSERT(mWork[it] == work);
			mWork.erase(mWork.begin() + it);
		}

		template<typename WORKTYPE, typename LESSTHAN>
		const typename SortedVectorContainer<WORKTYPE, LESSTHAN>::WorkType&
			SortedVectorContainer<WORKTYPE, LESSTHAN>::operator [](const size_t index) const
		{
			return mWork[index];
		}

		template<typename WORKTYPE, typename LESSTHAN> inline
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::Begin()
		{
			WorkVector accumulate;
			for (int i = 0; i < Concurrency::kMaxThreads; ++i)
			{
				accumulate.insert(accumulate.end(), mAdditions[i].begin(), mAdditions[i].end());
				mAdditions[i].clear();
			}
			std::sort(accumulate.begin(), accumulate.end());

			if (accumulate.size() > 0)
			{
				auto insertion = accumulate.begin();
				auto target = mWork.begin();

				while (insertion != accumulate.end() && target != mWork.end())
				{
					if (*insertion < *target)
					{
						target = mWork.emplace(target, Move(*insertion));
						++insertion;
						++target;
					}
				}

				mWork.insert(mWork.end(), insertion, accumulate.end());
			}
		}

		template<typename WORKTYPE, typename LESSTHAN> inline
		void SortedVectorContainer<WORKTYPE, LESSTHAN>::End()
		{
			WorkVector accumulate;
			for (int i = 0; i < Concurrency::kMaxThreads; ++i)
			{
				accumulate.insert(accumulate.end(), mDeletions[i].begin(), mDeletions[i].end());
				mDeletions[i].clear();
			}
			std::sort(accumulate.begin(), accumulate.end());

			if (accumulate.size() > 0)
			{
				auto icurrent = mWork.begin();
				for (auto ibegin = accumulate.begin(), iend = accumulate.end(); ibegin!=iend; ++ibegin)
				{
					while (*ibegin != *icurrent)
						++icurrent;
					CPF_ASSERT(*ibegin == *icurrent);
					icurrent = mWork.erase(icurrent);
				}
			}
		}

		template<typename WORKTYPE, typename LESSTHAN>
		int SortedVectorContainer<WORKTYPE, LESSTHAN>::_Find(const WorkType& work) const
		{
			LESSTHAN compare;
			int ilow = 0;
			int ihigh = int(mWork.size());
			int imid = 0;
			while (ilow < ihigh)
			{
				imid = ((ilow + ihigh) / 2);
				if (compare(mWork[imid], work))
				{
					ilow = imid + 1;
					continue;
				}
				if (compare(work, mWork[imid]))
				{
					ihigh = imid - 1;
					continue;
				}
				break;
			}
			return imid;
		}
	}
}

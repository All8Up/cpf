//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "Threading/Mutex.hpp"
#include "Functional.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		//////////////////////////////////////////////////////////////////////////
		class ContainerBase
		{
		public:
			virtual ~ContainerBase() {}
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
			Platform::Threading::Mutex mLock;
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

		private:
			using WorkVector = Vector<WorkType>;

			int _Find(const WorkType& work) const;

			Platform::Threading::Mutex mLock;
			WorkVector mWork;
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
			auto it = _Find(work);
			if (it>0)
			{
				mWork.emplace(mWork.begin()+it, Move(work));
				return;
			}
			mWork.emplace_back(Move(work));
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

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "Threading/Mutex.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class ContainerBase
		{
		public:
			virtual ~ContainerBase() {}
		};

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
	}
}

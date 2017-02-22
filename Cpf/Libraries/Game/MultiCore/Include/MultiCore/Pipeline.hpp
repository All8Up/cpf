//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "UnorderedMap.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Concurrency/Scheduler.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		/** @brief A multicore processing pipeline. */
		class Pipeline : public tRefCounted<iRefCounted>
		{
		public:
			static bool Create(Pipeline**);

			System* Install(System*);
			bool Remove(System*);

			bool Configure();

			System* GetSystem(SystemID id) const;
			System* GetSystem(const String& name) const;
			template <typename TYPE>
			TYPE* GetSystem(const String& name) const;

			Stage* GetStage(SystemID systemID, StageID stageID);

			const StageVector& GetStages() const;

			void operator ()(Concurrency::Scheduler::Queue&);

		private:
			Pipeline();
			~Pipeline();

			bool _ConfigureSystems() const;

			using SystemMap = UnorderedMap<SystemID, IntrusivePtr<System>>;
			SystemMap mSystemMap;
			StageVector mStages;

#ifdef CPF_DEBUG
			bool mChanged;
#endif
		};

		template <typename TYPE>
		TYPE* Pipeline::GetSystem(const String& name) const
		{
			return static_cast<TYPE*>(GetSystem(name));
		}
	}
}

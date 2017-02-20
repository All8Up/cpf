//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "GO/Types.hpp"
#include "Hash/Crc.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Container.hpp"
#include "String.hpp"

namespace Cpf
{
	namespace GO
	{
		class ObjectStage : public MultiCore::Stage
		{
		public:
			static constexpr MultiCore::StageID kID = "Object Stage"_crc64;

			using UpdateFunc = void(*)(MultiCore::System*, Object*);

			static bool Install();
			static bool Remove();

			void Emit(Concurrency::Scheduler::Queue&) override;

			// Interface.
			void AddUpdate(MultiCore::System* s, Object* o, UpdateFunc f);
			void RemoveUpdate(MultiCore::System* s, Object* o, UpdateFunc f);

		private:
			ObjectStage(MultiCore::System* owner, const String& name);

			static MultiCore::Stage* _Creator(MultiCore::System*, const String& name);

			// Implementation definitions.
			using UpdateTuple_t = Tuple<MultiCore::System*, Object*, UpdateFunc>;
			struct Compare
			{
				bool operator ()(const UpdateTuple_t& lhs, const UpdateTuple_t& rhs) const;
			};
			MultiCore::SortedVectorContainer<UpdateTuple_t, Compare> mWork;
			struct Caller
			{
				void Execute(Concurrency::ThreadContext&, const UpdateTuple_t& work);
			};

			static void _Update(Concurrency::ThreadContext& tc, void* context);

			MultiCore::System* mpSystem;
			Caller mCaller;
		};
	}
}

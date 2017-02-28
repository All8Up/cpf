//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vector.hpp"
#include "Hash/HashID.hpp"
#include "Stage.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		using OpcodeID = Hash::HashID<uint64_t, 12332>;
		struct StageOpcodeID
		{
			StageID mStage;
			OpcodeID mOpcode;
		};

		enum class ExecutionType
		{
			eFirst,
			eAll,
			eLast
		};

		struct OpcodeDependency
		{
			OpcodeID mDependent;
			Vector<OpcodeID> mDependencies;
		};

		class QueueBuilder
		{
		public:
			QueueBuilder();
			~QueueBuilder();

			void Add(StageID stageId, const ExecutionType opcode);
			void Add(const OpcodeDependency& dependency);
		};
	}
}

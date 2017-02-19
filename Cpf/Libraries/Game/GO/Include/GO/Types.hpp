//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Tuple.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "MultiCore/Stage.hpp"
#include "MultiCore/Container.hpp"
#include "MultiCore/Partitioning.hpp"
#include "Concurrency/ThreadContext.hpp"

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
		class Stage;
	}
}

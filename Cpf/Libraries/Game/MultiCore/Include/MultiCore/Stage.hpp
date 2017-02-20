//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Pair.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "RefCounted.hpp"
#include "MultiCore/Types.hpp"
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Service;

		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			// Interface definitions.
			using Dependency = Pair<ServiceID, StageID>;
			using Dependencies = Vector<Dependency>;

			// Construction/Destruction.
			Stage(Service* service, const String& name, const Dependencies& dependencies = Dependencies());
			virtual ~Stage();

			// Accessors.
			Service* GetService() const;
			StageID GetID() const;
			const String& GetName() const;

			// Comparisons.
			virtual bool operator == (const Stage& rhs) const;
			virtual bool operator != (const Stage& rhs) const;
			virtual bool operator > (const Stage& rhs) const;
			virtual bool operator < (const Stage& rhs) const;

			// Submission to the scheduler queue.
			virtual void Submit(Concurrency::Scheduler::Queue&) {}

		private:
			// Implementation data.
			Service* mpService;
			String mName;
			StageID mID;
			Dependencies mDependencies;
		};
	}
}

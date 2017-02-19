//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "RefCounted.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Pair.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Service;
		class DistributorBase;

		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			// Interface definitions.
			using Dependency = Pair<ServiceID, StageID>;
			using Dependencies = Vector<Dependency>;

			// Construction/Destruction.
			Stage(Service* service, StageID id, DistributorBase* distributor = nullptr, const Dependencies& dependencies = Dependencies());
			virtual ~Stage();

			// Accessors.
			Service* GetService() const;
			StageID GetID() const;
			DistributorBase* GetDistributor() const { return mpDistributor; }

			// Comparisons.
			virtual bool operator == (const Stage& rhs) const;
			virtual bool operator != (const Stage& rhs) const;
			virtual bool operator > (const Stage& rhs) const;
			virtual bool operator < (const Stage& rhs) const;

		private:
			// Implementation data.
			Service* mpService;
			StageID mID;
			Dependencies mDependencies;
			DistributorBase* mpDistributor;
		};
	}
}

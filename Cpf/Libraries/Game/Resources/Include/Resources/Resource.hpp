//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resources/Resources.hpp"
#include "Resources/ID.hpp"
#include "Resources/iResource.hpp"

namespace CPF
{
	namespace Resources
	{
		struct iCache;

		/** @brief The base resource class. */
		class ResourceBase : public iResource
		{
		public:
			int32_t CPF_STDCALL AddRef() override;
			int32_t CPF_STDCALL Release() override;

			void CPF_STDCALL Initialize(ID, iCache*) override;

		protected:
			ResourceBase(iUnknown*);
			virtual ~ResourceBase();

		private:
			int32_t mRefCount;
			ID mID;
			iCache* mpCache;
		};
	}
}

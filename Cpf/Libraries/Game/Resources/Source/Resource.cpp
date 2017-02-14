///
#include "Resources/Resource.hpp"
#include "Resources/Cache.hpp"

using namespace Cpf;
using namespace Resources;

/**
 * @brief Standard add reference.
 * @return Number of outstanding references.
 */
int32_t ResourceBase::AddRef()
{
	return ++mRefCount;
}

/**
 * @brief Modified release, notifies the attached cache when at 1.
 * @return The number of remaining references.
 */
int32_t ResourceBase::Release()
{
	if (--mRefCount==0)
	{
		delete this;
		return 0;
	}
	if (mRefCount==1)
	{
		// Only the cache has an outstanding reference, let it know.
		CPF_ASSERT(mpCache != nullptr);
		mpCache->LastReference(mID);
		// NOTE: likely to be deleted by the cache, so can't reference 'this' anymore.
		return 1;
	}
	return mRefCount;
}

/**
 * @brief Constructor.
 * @param id The identifier.
 * @param [in,out] cache If non-null, the cache.
 */
ResourceBase::ResourceBase(ID id, Cache* cache)
	: mRefCount(1)
	, mID(id)
	, mpCache(cache)
{}

/** @brief Destructor. */
ResourceBase::~ResourceBase()
{}

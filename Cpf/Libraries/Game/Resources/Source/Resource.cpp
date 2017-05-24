///
#include "Resources/Resource.hpp"
#include "Resources/iCache.hpp"

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

void CPF_STDCALL ResourceBase::Initialize(ID id, iCache* cache)
{
	mID.mID = id.mID;
	mpCache = cache;
}

/**
 * @brief Constructor.
 * @param id The identifier.
 * @param [in,out] cache If non-null, the cache.
 */
ResourceBase::ResourceBase(iBase*)
	: mRefCount(1)
	, mID(kInvalidID)
{}

/** @brief Destructor. */
ResourceBase::~ResourceBase()
{}

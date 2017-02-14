/**
* @brief Implements the hash initializer class.
*/
#include "Hash/Hash.hpp"

using namespace Cpf;
using namespace Platform;

namespace
{
	/** @brief Number of references to this library. */
	int s_RefCount = 0;
}


/**
* @brief Initialize the library.
* @return An int.
*/
CPF_EXPORT_HASH int HashInitializer::Install()
{
	return ++s_RefCount;
}

/**
* @brief Release a reference count and potentially shutdown the library.
* @return An int.
*/
CPF_EXPORT_HASH int HashInitializer::Remove()
{
	return --s_RefCount;
}

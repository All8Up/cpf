/**
* @brief Implements the containers initializer class.
*/
#include "Collections.hpp"

/**
 * @brief Array allocation operator.
 * @param size		 The size.
 * @param pName		 The name.
 * @param flags		 The flags.
 * @param debugFlags The debug flags.
 * @param file		 The file.
 * @param line		 The line.
 * @return The allocated array.
 */
CPF_EXPORT_COLLECTIONS void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
	return operator new[](size);
}


/**
 * @brief Array allocation operator.
 * @param size			  The size.
 * @param alignment		  The alignment.
 * @param alignmentOffset The alignment offset.
 * @param pName			  The name.
 * @param flags			  The flags.
 * @param debugFlags	  The debug flags.
 * @param file			  The file.
 * @param line			  The line.
 * @return The allocated array.
 */
CPF_EXPORT_COLLECTIONS void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)alignment; (void)alignmentOffset; (void)pName; (void)flags; (void)debugFlags; (void)file; (void)line;
	return operator new[](size);
}

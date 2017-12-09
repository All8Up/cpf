//////////////////////////////////////////////////////////////////////////
#pragma once


#ifdef CPF_COMPILER_HAS_ALIGNAS
/**
 * @brief Macro to specify the alignment requirement of a class or structure.
 * @param size The alignment restriction.
 */
#	define CPF_ALIGN( size ) alignas(size)


//
#else
//

/**
 * @brief Macro to specify the alignment requirement of a class or structure.
 * @param size The alignment restriction.
 */
#	define CPF_ALIGN( size ) __declspec(align(size))


// CPF_COMPILER_HAS_ALIGNAS
#endif

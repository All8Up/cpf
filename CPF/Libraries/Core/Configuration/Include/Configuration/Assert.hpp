//////////////////////////////////////////////////////////////////////////
#pragma once


/**
 * @brief General assertion.
 * @param exp The expression to assert on.
 */
#define CPF_ASSERT(exp)		{if(!(exp)) CPF_DEBUG_BREAK;}

/**
 * @brief Always assert.
 */
#define CPF_ASSERT_ALWAYS	{CPF_DEBUG_BREAK;}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "GOM/Result.hpp"
#include <Python.h>

namespace Cpf
{
	namespace GOM
	{
		namespace py
		{
			struct Result
			{
				PyObject_HEAD
				GOM::Result mResult;
			};

			bool AddResultType(PyObject* parent);
		}
	}
}

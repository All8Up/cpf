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
			extern PyTypeObject Result_type;

			bool AddResultType(PyObject* parent);
		}
	}
}

#define GOMResult_Check(v)      (Py_TYPE(v) == &Cpf::GOM::py::Result_type)

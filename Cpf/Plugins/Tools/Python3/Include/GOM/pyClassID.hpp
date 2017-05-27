//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "GOM/iBase.hpp"
#include <Python.h>

namespace Cpf
{
	namespace GOM
	{
		namespace py
		{
			struct ClassID
			{
				PyObject_HEAD
				GOM::ClassID mID;
			};
			extern PyTypeObject ClassID_type;

			bool AddClassIDType(PyObject* parent);
		}
	}
}


#define GOMClassID_Check(v)      (Py_TYPE(v) == &Cpf::GOM::py::ClassID_type)

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
			struct InterfaceID
			{
				PyObject_HEAD
				GOM::InterfaceID mID;
			};
			extern PyTypeObject InterfaceID_type;


			bool AddInterfaceIDType(PyObject* parent);
		}
	}
}


#define GOMInterfaceID_Check(v) (Py_TYPE(v) == &Cpf::GOM::py::InterfaceID_type)

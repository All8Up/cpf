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

			bool AddInterfaceIDType(PyObject* parent);
		}
	}
}

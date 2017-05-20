//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "GOM/iUnknown.hpp"
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

			bool AddClassIDType(PyObject* parent);
		}
	}
}

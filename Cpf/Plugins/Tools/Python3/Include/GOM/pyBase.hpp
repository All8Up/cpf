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
			struct Base
			{
				PyObject_HEAD
				iBase* mpBase;
			};

			bool AddBaseType(PyObject* parent);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Python.h>
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Plugin
	{
		namespace py
		{
			struct Registry
			{
				PyObject_HEAD
				GOM::iBase* mpBase;
				PyObject* mpIID;
			};
			extern PyTypeObject PluginRegistry_type;

			extern "C" PyObject* CPF_STDCALL PyCreateRegistry(PyObject*, PyObject* args);

			bool AddRegistryType(PyObject* parent);
		}
	}
}

#define PluginRegistry_Check(v)      (Py_TYPE(v) == &Cpf::Plugin::py::PluginRegistry_type)

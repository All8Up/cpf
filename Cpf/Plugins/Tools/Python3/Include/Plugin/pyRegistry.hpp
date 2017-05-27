//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Python.h>
#include "GOM/pyBase.hpp"

namespace Cpf
{
	namespace Plugin
	{
		namespace py
		{
			struct Registry
			{
				GOM::py::Base mBase;
				PyObject* mpIID;
			};
			extern PyTypeObject PluginRegistry_type;

			extern "C" PyObject* CPF_STDCALL PyCreateRegistry(PyObject*, PyObject* args);

			bool AddRegistryType(PyObject* parent);
		}
	}
}

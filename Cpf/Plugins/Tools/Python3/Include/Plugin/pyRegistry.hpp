//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Plugin/iRegistry.hpp"
#include <Python.h>

namespace Cpf
{
	namespace Plugin
	{
		namespace py
		{
			struct Registry
			{
				PyObject_HEAD
				iRegistry* mpRegistry;
			};

			bool AddRegistryType(PyObject* parent);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "Plugin/pyMethods.hpp"
#include "Plugin/pyRegistry.hpp"

using namespace Cpf;


//////////////////////////////////////////////////////////////////////////
PyMethodDef Plugin::py::CpfPlugin_methods[] =
{
	{ "create_registry", (PyCFunction)Plugin::py::PyCreateRegistry, METH_VARARGS, PyDoc_STR("Create a new registry instance.") },
	{ nullptr, nullptr }
};

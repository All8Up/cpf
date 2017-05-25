//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "Plugin/pyMethods.hpp"
#include "Python3.hpp"
#include "Plugin/pyRegistry.hpp"

using namespace Cpf;

extern Tools::Python3* s_Python3;

//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL PyCreateRegistry(PyObject*, PyObject* args)
{
	if (s_Python3)
	{
		Plugin::py::Registry* regy = PyObject_New(Plugin::py::Registry, reinterpret_cast<PyTypeObject*>(&Plugin::py::PluginRegistry_type));
		regy->mBase.mpBase = nullptr;
		s_Python3->CreateRegistry(reinterpret_cast<Plugin::iRegistry**>(&regy->mBase.mpBase));
		return reinterpret_cast<PyObject*>(regy);
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef Plugin::py::CpfPlugin_methods[] =
{
	{ "create_registry", (PyCFunction)PyCreateRegistry, METH_VARARGS, PyDoc_STR("Create a new registry instance.") },
	{ nullptr, nullptr }
};

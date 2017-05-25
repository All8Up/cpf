//////////////////////////////////////////////////////////////////////////
#include "Plugin/pyModule.hpp"
#include "Plugin/pyRegistry.hpp"
#include "Plugin/pyMethods.hpp"

using namespace Cpf;
using namespace Plugin;

static PyModuleDef CpfPluginModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf.plugin",
	"Plugin module integration.",
	-1,
	py::CpfPlugin_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

bool py::AddModule(PyObject* parent)
{
	PyObject* module = PyModule_Create(&CpfPluginModuleDef);
	if (module == nullptr)
	{
		Py_DECREF(parent);
		return false;
	}
	PyModule_AddObject(parent, "plugin", module);

	return AddRegistryType(module);
}

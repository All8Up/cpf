//////////////////////////////////////////////////////////////////////////
#include "Plugin/pyRegistry.hpp"
#include "Plugin/iRegistry.hpp"
#include "GOM/pyResult.hpp"

using namespace Cpf;
using namespace Plugin;

/*
GOM::Result CPF_STDCALL Install(GOM::ClassID cid, iClassInstance* clsInst) = 0;
GOM::Result CPF_STDCALL Remove(GOM::ClassID cid) = 0;
GOM::Result CPF_STDCALL Exists(GOM::ClassID cid) = 0;
GOM::Result CPF_STDCALL Create(iBase* outer, GOM::ClassID cid, GOM::InterfaceID iid, void** result) = 0;
GOM::Result CPF_STDCALL ClassInstall(int32_t count, const IID_CID* pairs) = 0;
GOM::Result CPF_STDCALL ClassRemove(int32_t count, const IID_CID* pairs) = 0;
GOM::Result CPF_STDCALL GetClasses(GOM::InterfaceID id, int32_t* count, GOM::ClassID* cid) = 0;
GOM::Result CPF_STDCALL InstanceInstall(GOM::InterfaceID id, void* instance) = 0;
GOM::Result CPF_STDCALL InstanceRemove(GOM::InterfaceID id) = 0;
GOM::Result CPF_STDCALL GetInstances(GOM::InterfaceID id, void** outIface) = 0;
*/

extern "C" PyObject* CPF_STDCALL RegistryLoad(py::Registry* self, PyObject* args)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "s:load", &name))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	{
		if (Succeeded(reinterpret_cast<iRegistry*>(self->mBase.mpBase)->Load(name)))
			return PyBool_FromLong(1);
		PyErr_SetString(PyExc_RuntimeError, "Plugin load failure.");
	}
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryCanUnload(py::Registry* self, PyObject* args)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "s:can_unload", &name))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}

	if (Succeeded(reinterpret_cast<iRegistry*>(self->mBase.mpBase)->CanUnload(name)))
		return PyBool_FromLong(1);
	return PyBool_FromLong(0);
}

extern "C" PyObject* CPF_STDCALL RegistryUnload(py::Registry* self, PyObject* args)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "s:unload", &name))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	if (Succeeded(reinterpret_cast<iRegistry*>(self->mBase.mpBase)->Unload(name)))
		return PyBool_FromLong(1);
	return PyBool_FromLong(0);
}

extern "C" PyObject* CPF_STDCALL RegistryExists(py::Registry* self, PyObject* args)
{
	
}

PyMethodDef PluginRegistry_methods[] =
{
	{ "load", (PyCFunction)RegistryLoad, METH_VARARGS, PyDoc_STR("Attempt to load a plugin.") },
	{ "can_unload", (PyCFunction)RegistryCanUnload, METH_VARARGS, PyDoc_STR("Test if a plugin can be unloaded.") },
	{ "unload", (PyCFunction)RegistryUnload, METH_VARARGS, PyDoc_STR("Attempt to unload a plugin.") },
	{ nullptr, nullptr }
};

PyTypeObject py::PluginRegistry_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"plugin.Registry",			/* tp_name */
	sizeof(py::Registry),		/* tp_basicsize */
	0,							/* tp_itemsize */
	0,							/* tp_dealloc */
	0,							/* tp_print */
	0,							/* tp_getattr */
	0,							/* tp_setattr */
	0,							/* tp_reserved */
	0,							/* tp_repr */
	0,							/* tp_as_number */
	0,							/* tp_as_sequence */
	0,							/* tp_as_mapping */
	0,							/* tp_hash  */
	0,							/* tp_call */
	0,							/* tp_str */
	0,							/* tp_getattro */
	0,							/* tp_setattro */
	0,							/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,			/* tp_flags */
	"Cpf objects",				/* tp_doc */
	nullptr,					/* tp_traverse */
	nullptr,					/* tp_clear */
	nullptr,					/* tp_richcompare */
	0,							/* tp_weaklistoffset */
	nullptr,					/* tp_iter */
	nullptr,					/* tp_iternext */
	PluginRegistry_methods,		/* tp_methods */
	nullptr,					/* tp_members */
	nullptr,					/* tp_getset */
	nullptr,					/* tp_base */
};


//////////////////////////////////////////////////////////////////////////
extern PyTypeObject GOMBase_type;

bool py::AddRegistryType(PyObject* parent)
{
	PluginRegistry_type.tp_base = &GOMBase_type;
	PluginRegistry_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PluginRegistry_type) < 0)
		return false;
	Py_INCREF(&PluginRegistry_type);
	PyModule_AddObject(parent, "Registry", reinterpret_cast<PyObject*>(&PluginRegistry_type));

	return true;
}

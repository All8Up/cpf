//////////////////////////////////////////////////////////////////////////
#include "Plugin/pyRegistry.hpp"
#include "Plugin/iRegistry.hpp"
#include "GOM/pyResult.hpp"
#include "GOM/pyInterfaceID.hpp"
#include "GOM/pyClassID.hpp"
#include <structmember.h>
#include "Python3.hpp"

using namespace Cpf;
using namespace Plugin;

extern Tools::Python3* s_Python3;
PyObject* s_pRegistryIID = nullptr;


extern "C" PyObject* CPF_STDCALL py::PyCreateRegistry(PyObject*, PyObject* args)
{
	if (s_Python3)
	{
		py::Registry* regy = PyObject_New(Plugin::py::Registry, reinterpret_cast<PyTypeObject*>(&Plugin::py::PluginRegistry_type));
		regy->mpBase = nullptr;
		regy->mpIID = s_pRegistryIID;
		s_Python3->CreateRegistry(reinterpret_cast<Plugin::iRegistry**>(&regy->mpBase));
		return reinterpret_cast<PyObject*>(regy);
	}
	return nullptr;
}

extern "C" int CPF_STDCALL New_Registry(py::Registry* self, PyObject* args, PyObject* kwds)
{
	CPF_ASSERT(PluginRegistry_Check(self));
	self->mpIID = s_pRegistryIID;
	return 0;
}

extern "C" void CPF_STDCALL Free_Registry(py::Registry* self)
{
	self->mpBase->Release();
	PyObject_Del(self);
}

extern "C" PyObject* CPF_STDCALL RegistryLoad(py::Registry* self, PyObject* args)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "s:load", &name))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	{
		if (Succeeded(reinterpret_cast<iRegistry*>(self->mpBase)->Load(name)))
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

	if (Succeeded(reinterpret_cast<iRegistry*>(self->mpBase)->CanUnload(name)))
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
	if (Succeeded(reinterpret_cast<iRegistry*>(self->mpBase)->Unload(name)))
		return PyBool_FromLong(1);
	return PyBool_FromLong(0);
}

extern "C" PyObject* CPF_STDCALL RegistryInstall(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL Install(GOM::ClassID cid, iClassInstance* clsInst) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryRemove(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL Remove(GOM::ClassID cid) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryExists(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL Exists(GOM::ClassID cid) = 0;
	PyObject* classId = nullptr;
	if (PyArg_ParseTuple(args, "O:exists", &classId))
	{
		if (classId && GOMClassID_Check(classId))
		{
			if (Succeeded(reinterpret_cast<iRegistry*>(self->mpBase)->
				Exists(reinterpret_cast<GOM::py::ClassID*>(classId)->mID)))
			{
				return PyBool_FromLong(1);
			}
			return PyBool_FromLong(0);
		}
	}
	PyErr_SetString(PyExc_RuntimeError, "Invalid arguments.");
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryCreate(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL Create(iBase* outer, GOM::ClassID cid, GOM::InterfaceID iid, void** result) = 0;
	// Python conversion:
	//	Throws exceptions on error/failure.
	//	Returns the object as a result.
	//	cid, iid, [outer]
	PyObject* classId = nullptr;
	PyObject* interfaceId = nullptr;
	PyObject* outer = nullptr;
	if (PyArg_ParseTuple(args, "OO|O:create", &classId, &interfaceId, &outer))
	{
		if (GOMClassID_Check(classId) && GOMInterfaceID_Check(interfaceId))
		{
			GOM::iBase* result = nullptr;
			GOM::py::ClassID* cid = reinterpret_cast<GOM::py::ClassID*>(classId);
			GOM::py::InterfaceID* iid = reinterpret_cast<GOM::py::InterfaceID*>(interfaceId);
			GOM::iBase* outerPtr = outer ? reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(outer, nullptr)) : nullptr;

			if (Succeeded(reinterpret_cast<iRegistry*>(self->mpBase)->Create(outerPtr, cid->mID, iid->mID, reinterpret_cast<void**>(&result))))
			{
				auto capsule = PyCapsule_New(reinterpret_cast<void*>(result), nullptr, [](PyObject* obj) {
					GOM::iBase* base = reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(obj, nullptr));
					base->Release();
				});
				return capsule;
			}
			PyErr_SetString(PyExc_RuntimeError, "Failed to create the desired instance.");
			return nullptr;
		}
	}

	PyErr_SetString(PyExc_RuntimeError, "Invalid arguments.");
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryClassInstall(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL ClassInstall(int32_t count, const IID_CID* pairs) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryClassRemove(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL ClassRemove(int32_t count, const IID_CID* pairs) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryGetClasses(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL GetClasses(GOM::InterfaceID id, int32_t* count, GOM::ClassID* cid) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryInstanceInstall(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL InstanceInstall(GOM::InterfaceID id, void* instance) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryInstanceRemove(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL InstanceRemove(GOM::InterfaceID id) = 0;
	return nullptr;
}

extern "C" PyObject* CPF_STDCALL RegistryGetInstance(py::Registry* self, PyObject* args)
{
	// GOM::Result CPF_STDCALL GetInstance(GOM::InterfaceID id, void** outIface) = 0;
	return nullptr;
}


//////////////////////////////////////////////////////////////////////////

PyMethodDef PluginRegistry_methods[] =
{
	{ "load", (PyCFunction)RegistryLoad, METH_VARARGS, PyDoc_STR("Attempt to load a plugin.") },
	{ "can_unload", (PyCFunction)RegistryCanUnload, METH_VARARGS, PyDoc_STR("Test if a plugin can be unloaded.") },
	{ "unload", (PyCFunction)RegistryUnload, METH_VARARGS, PyDoc_STR("Attempt to unload a plugin.") },
	{ "install", (PyCFunction)RegistryInstall, METH_VARARGS, PyDoc_STR("Attempt to install a plugin class instance.") },
	{ "remove", (PyCFunction)RegistryRemove, METH_VARARGS, PyDoc_STR("Attempt to remove a plugin class instance.") },
	{ "exists", (PyCFunction)RegistryExists, METH_VARARGS, PyDoc_STR("Test if a class instance is installed.") },
	{ "create", (PyCFunction)RegistryCreate, METH_VARARGS, PyDoc_STR("Create an instance.") },
	{ "class_install", (PyCFunction)RegistryClassInstall, METH_VARARGS, PyDoc_STR("Install a instance and class id pairs.") },
	{ "class_remove", (PyCFunction)RegistryClassRemove, METH_VARARGS, PyDoc_STR("Attempt to remove instance and class id pairs.") },
	{ "get_classes", (PyCFunction)RegistryGetClasses, METH_VARARGS, PyDoc_STR("Get the list of class id's associated with the interface id.") },
	{ "instance_install", (PyCFunction)RegistryInstanceInstall, METH_VARARGS, PyDoc_STR("Install an instance for a given interface id.") },
	{ "instance_remove", (PyCFunction)RegistryInstanceRemove, METH_VARARGS, PyDoc_STR("Remove an instance for the given interface id.") },
	{ "get_instance", (PyCFunction)RegistryGetInstance, METH_VARARGS, PyDoc_STR("Get the instance associated with the interface id.") },
	{ nullptr, nullptr }
};

PyMemberDef PluginRegistry_members[] =
{
	{ "iid", T_OBJECT, offsetof(py::Registry, mpIID), READONLY },
	{ nullptr }
};

PyTypeObject py::PluginRegistry_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"plugin.Registry",			/* tp_name */
	sizeof(py::Registry),		/* tp_basicsize */
	0,							/* tp_itemsize */
	(destructor)Free_Registry,	/* tp_dealloc */
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
	PluginRegistry_members,		/* tp_members */
	nullptr,					/* tp_getset */
	nullptr,					/* tp_base */
	nullptr,					/* tp_dict */
	nullptr,					/* tp_descr_get */
	nullptr,					/* tp_descr_set */
	0,							/* tp_dictoffset */
	nullptr,					/* tp_init */
	nullptr,					/* tp_alloc */
	(newfunc)New_Registry,		/* tp_new */
	nullptr,					/* tp_free */
	nullptr,					/* tp_is_gc */
	nullptr,					/* tp_bases */
	nullptr,					/* tp_mro */
	nullptr,					/* tp_cache */
	nullptr,					/* tp_subclasses */
	nullptr,					/* tp_weaklist */
	nullptr,					/* tp_del */
	0,							/* tp_version_tag */
	nullptr						/* tp_finalize */
};


//////////////////////////////////////////////////////////////////////////
bool py::AddRegistryType(PyObject* parent)
{
	s_pRegistryIID = reinterpret_cast<PyObject*>(PyObject_New(GOM::py::InterfaceID, &GOM::py::InterfaceID_type));

	if (PyType_Ready(&PluginRegistry_type) < 0)
		return false;
	Py_INCREF(&PluginRegistry_type);

	if (PyModule_AddObject(parent, "Registry", reinterpret_cast<PyObject*>(&PluginRegistry_type))==0)
		return true;
	return false;
}

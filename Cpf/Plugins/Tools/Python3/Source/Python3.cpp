//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include <Python.h>
#include "rttr/registration.h"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;
using namespace Tools;

Python3::Python3(iUnknown*)
{}

Python3::~Python3()
{}

GOM::Result CPF_STDCALL Python3::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iPython3*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

//////////////////////////////////////////////////////////////////////////
RTTR_REGISTRATION
{
	rttr::registration::class_<Plugin::iRegistry>("Cpf::Plugin::iRegistry")
		(
			rttr::metadata("ScriptExport", true)
		)
		.method("Load", &Plugin::iRegistry::Load)
		.method("Install", &Plugin::iRegistry::Install)
		.method("Remove", &Plugin::iRegistry::Remove)
		.method("Exists", &Plugin::iRegistry::Exists)
		.method("Create", &Plugin::iRegistry::Create)
		.method("ClassInstall", &Plugin::iRegistry::ClassInstall)
		.method("ClassRemove", &Plugin::iRegistry::ClassRemove)
		.method("GetClasses", &Plugin::iRegistry::GetClasses)
		.method("InstanceInstall", &Plugin::iRegistry::InstanceInstall)
		.method("InstanceRemove", &Plugin::iRegistry::InstanceRemove)
		.method("GetInstance", &Plugin::iRegistry::GetInstance)
	;
	rttr::registration::class_<GOM::Result>("Cpf::GOM::Result")
		(
			rttr::metadata("ScriptExport", true)
		)
		.property("Error", &GOM::Result::GetError, &GOM::Result::SetError)
		.property("SubSystem", &GOM::Result::GetSubSystem, &GOM::Result::SetSubSystem)
		.property("Value", &GOM::Result::GetValue, &GOM::Result::SetValue)
	;
}


//////////////////////////////////////////////////////////////////////////
extern PyMethodDef CpfGOM_methods[];
static PyModuleDef cpfModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf",
	"Core module integration with the Cpf frameworks.",
	-1,
	CpfGOM_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

static PyModuleDef CpfGomModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf.gom",
	"GOM module integration.",
	-1,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

struct PyObject_GOMResult
{
	PyObject_HEAD
	GOM::Result mResult;
};


//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL CpfGOMSucceeded(PyObject_GOMResult*, PyObject* args)
{
	PyObject_GOMResult* result;
	if (!PyArg_ParseTuple(args, "O:succeeded", &result))
		return nullptr;
	return PyBool_FromLong(result->mResult.Error == 0);
}

extern "C" PyObject* CPF_STDCALL CpfGOMFailed(PyObject_GOMResult*, PyObject* args)
{
	PyObject_GOMResult* result;
	if (!PyArg_ParseTuple(args, "O:failed", &result))
		return nullptr;
	return PyBool_FromLong(result->mResult.Error != 0);
}


PyMethodDef CpfGOM_methods[] =
{
	{ "succeeded", (PyCFunction)CpfGOMSucceeded, METH_VARARGS, PyDoc_STR("Determine if a call succeeded.") },
	{ "failed", (PyCFunction)CpfGOMFailed, METH_VARARGS, PyDoc_STR("Determine if a call failed.") },
	{ nullptr, nullptr }
};

//////////////////////////////////////////////////////////////////////////
// GOMResult
extern PyMethodDef GOMResult_methods[];
extern PyGetSetDef GOMResult_getseters[];

extern "C" int CPF_STDCALL Init_GOMResult(PyObject_GOMResult* self, PyObject* args, PyObject* kwds)
{
	char* name = nullptr;
	self->mResult = GOM::Result{ 0, 0, 0 };
	char* keys[] = {"error", "subsystem", "value"};
	if (!PyArg_ParseTuple(args, "|s", &name))
	{
		return -1;
	}
	return 0;
}

static PyTypeObject GOMResult_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.Result",				/* tp_name */
	sizeof(PyObject_GOMResult),	/* tp_basicsize */
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
	GOMResult_methods,			/* tp_methods */
	nullptr,					/* tp_members */
	GOMResult_getseters,		/* tp_getset */
	nullptr,					/* tp_base */
	nullptr,					/* tp_dict */
	nullptr,					/* tp_descr_get */
	nullptr,					/* tp_descr_set */
	0,							/* tp_dictoffset */
	(initproc)Init_GOMResult,	/* tp_init */
	nullptr,					/* tp_alloc */
	nullptr,					/* tp_new */
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

extern "C" void CPF_STDCALL Dealloc_GOMResult(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

#define GOMResult_Check(v)      (Py_TYPE(v) == &GOMResult_type)

/* PyObject_GOMResult methods */
extern "C" PyObject* CPF_STDCALL GOMResult_IsSuccess(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_success"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error == 0);
}

extern "C" PyObject* CPF_STDCALL GOMResult_IsError(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_error"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error != 0);
}


//////////////////////////////////////////////////////////////////////////
PyMethodDef GOMResult_methods[] =
{
	{"is_error", (PyCFunction)GOMResult_IsError, METH_VARARGS, PyDoc_STR("Determine if the result indicates an error occurred.")},
	{"is_success", (PyCFunction)GOMResult_IsSuccess, METH_VARARGS, PyDoc_STR("Determine if the result indicates success.")},
	{nullptr, nullptr}
};


//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMResult_get_error(PyObject_GOMResult* self, void*)
{
	return PyLong_FromLong(self->mResult.Error);
}

extern "C" int CPF_STDCALL GOMResult_set_error(PyObject_GOMResult* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.Error = v;
	return 0;
}

extern "C" PyObject* CPF_STDCALL GOMResult_get_subsystem(PyObject_GOMResult* self, void*)
{
	return PyLong_FromLong(self->mResult.SubSystem);
}

extern "C" int CPF_STDCALL GOMResult_set_subsystem(PyObject_GOMResult* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.SubSystem = v;
	return 0;
}

extern "C" PyObject* CPF_STDCALL GOMResult_get_value(PyObject_GOMResult* self, void*)
{
	return PyLong_FromLong(self->mResult.Value);
}

extern "C" int CPF_STDCALL GOMResult_set_value(PyObject_GOMResult* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.Value = v;
	return 0;
}

PyGetSetDef GOMResult_getseters[] =
{
	{ "error", (getter)GOMResult_get_error, (setter)GOMResult_set_error, nullptr, nullptr },
	{ "subsystem", (getter)GOMResult_get_subsystem, (setter)GOMResult_set_subsystem, NULL, NULL },
	{ "value", (getter)GOMResult_get_value, (setter)GOMResult_set_value, NULL, NULL },
	{ NULL }
};


//////////////////////////////////////////////////////////////////////////
// GOMClassID
struct PyObject_GOMClassID
{
	PyObject_HEAD
	GOM::ClassID mID;
};

extern "C" int CPF_STDCALL Init_GOMClassID(PyObject_GOMClassID* self, PyObject* args, PyObject* kwds)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "|s", &name))
	{
		self->mID = GOM::ClassID(0);
		return -1;
	}
	self->mID = GOM::ClassID(name ? Hash::Crc64(name, ::strlen(name)) : 0);
	return 0;
}

extern PyGetSetDef GOMClassID_getseters[];

static PyTypeObject GOMClassID_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.ClassID",				/* tp_name */
	sizeof(PyObject_GOMClassID),	/* tp_basicsize */
	0,							/* tp_itemsize */
	nullptr,					/* tp_dealloc */
	nullptr,					/* tp_print */
	nullptr,					/* tp_getattr */
	nullptr,					/* tp_setattr */
	nullptr,					/* tp_reserved */
	nullptr,					/* tp_repr */
	nullptr,					/* tp_as_number */
	nullptr,					/* tp_as_sequence */
	nullptr,					/* tp_as_mapping */
	nullptr,					/* tp_hash  */
	nullptr,					/* tp_call */
	nullptr,					/* tp_str */
	nullptr,					/* tp_getattro */
	nullptr,					/* tp_setattro */
	nullptr,					/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,			/* tp_flags */
	"Cpf objects",				/* tp_doc */
	nullptr,					/* tp_traverse */
	nullptr,					/* tp_clear */
	nullptr,					/* tp_richcompare */
	0,							/* tp_weaklistoffset */
	nullptr,					/* tp_iter */
	nullptr,					/* tp_iternext */
	nullptr,					/* tp_methods */
	nullptr,					/* tp_members */
	GOMClassID_getseters,		/* tp_getset */
	nullptr,					/* tp_base */
	nullptr,					/* tp_dict */
	nullptr,					/* tp_descr_get */
	nullptr,					/* tp_descr_set */
	0,							/* tp_dictoffset */
	(initproc)Init_GOMClassID,	/* tp_init */
	nullptr,					/* tp_alloc */
	nullptr,					/* tp_new */
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
extern "C" void CPF_STDCALL Dealloc_GOMClassID(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

#define GOMClassID_Check(v)      (Py_TYPE(v) == &GOMClassID_type)


//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMClassID_get_id(PyObject_GOMClassID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMClassID_set_id(PyObject_GOMClassID* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLongLong(value);
	self->mID = GOM::ClassID(v);
	return 0;
}

PyGetSetDef GOMClassID_getseters[] =
{
	{ "id", (getter)GOMClassID_get_id, (setter)GOMClassID_set_id, nullptr, nullptr },
	{ NULL }
};


//////////////////////////////////////////////////////////////////////////
// GOMInterfaceID
struct PyObject_GOMInterfaceID
{
	PyObject_HEAD
	GOM::InterfaceID mID;
};

extern PyGetSetDef GOMInterfaceID_getseters[];

extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(PyObject_GOMInterfaceID* self);

extern "C" int CPF_STDCALL Init_GOMInterfaceID(PyObject_GOMInterfaceID* self, PyObject* args, PyObject* kwds)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "|s", &name))
	{
		self->mID = GOM::InterfaceID(0);
		return -1;
	}
	self->mID = GOM::InterfaceID(name ? Hash::Crc64(name, ::strlen(name)) : 0);
	return 0;
}


static PyTypeObject GOMInterfaceID_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.InterfaceID",						/* tp_name */
	sizeof(PyObject_GOMInterfaceID),		/* tp_basicsize */
	0,										/* tp_itemsize */
	(destructor)Dealloc_GOMInterfaceID,		/* tp_dealloc */
	0,										/* tp_print */
	0,										/* tp_getattr */
	0,										/* tp_setattr */
	0,										/* tp_reserved */
	0,										/* tp_repr */
	0,										/* tp_as_number */
	0,										/* tp_as_sequence */
	0,										/* tp_as_mapping */
	0,										/* tp_hash  */
	0,										/* tp_call */
	0,										/* tp_str */
	0,										/* tp_getattro */
	0,										/* tp_setattro */
	0,										/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,						/* tp_flags */
	"Cpf objects",							/* tp_doc */
	nullptr,								/* tp_traverse */
	nullptr,								/* tp_clear */
	nullptr,								/* tp_richcompare */
	0,										/* tp_weaklistoffset */
	nullptr,								/* tp_iter */
	nullptr,								/* tp_iternext */
	nullptr,								/* tp_methods */
	nullptr,								/* tp_members */
	GOMInterfaceID_getseters,				/* tp_getset */
	nullptr,								/* tp_base */
	nullptr,								/* tp_dict */
	nullptr,								/* tp_descr_get */
	nullptr,								/* tp_descr_set */
	0,										/* tp_dictoffset */
	(initproc)Init_GOMInterfaceID,			/* tp_init */
	nullptr,								/* tp_alloc */
	nullptr,								/* tp_new */
	nullptr,								/* tp_free */
	nullptr,								/* tp_is_gc */
	nullptr,								/* tp_bases */
	nullptr,								/* tp_mro */
	nullptr,								/* tp_cache */
	nullptr,								/* tp_subclasses */
	nullptr,								/* tp_weaklist */
	nullptr,								/* tp_del */
	0,										/* tp_version_tag */
	nullptr									/* tp_finalize */
};


//////////////////////////////////////////////////////////////////////////
extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(PyObject_GOMInterfaceID *self)
{
	PyObject_Del(self);
}

#define GOMInterfaceID_Check(v)      (Py_TYPE(v) == &GOMInterfaceID_type)

extern "C" PyObject_GOMInterfaceID* CPF_STDCALL newGOMInterfaceID(PyObject *arg)
{
	(void)arg;
	PyObject_GOMInterfaceID *self;
	self = PyObject_New(PyObject_GOMInterfaceID, &GOMInterfaceID_type);
	if (self == nullptr)
		return nullptr;
	self->mID = GOM::InterfaceID(0);
	return self;
}

//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMInterfaceID_get_id(PyObject_GOMInterfaceID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMInterfaceID_set_id(PyObject_GOMInterfaceID* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLongLong(value);
	self->mID = GOM::InterfaceID(v);
	return 0;
}

PyGetSetDef GOMInterfaceID_getseters[] =
{
	{ "id", (getter)GOMInterfaceID_get_id, (setter)GOMInterfaceID_set_id, nullptr, nullptr },
	{ NULL }
};

//////////////////////////////////////////////////////////////////////////
// PluginRegistry
struct PyObject_PluginRegistry
{
	PyObject_HEAD
	Plugin::iRegistry* mpRegistry;
};

static PyTypeObject PluginRegistry_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.Registry",				/* tp_name */
	sizeof(PyObject_PluginRegistry),	/* tp_basicsize */
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
	nullptr,					/* tp_methods */
	nullptr,					/* tp_members */
	nullptr,					/* tp_getset */
	nullptr,					/* tp_base */
};

#if 0
//////////////////////////////////////////////////////////////////////////
extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

#define GOMInterfaceID_Check(v)      (Py_TYPE(v) == &GOMInterfaceID_type)

extern "C" PyObject_GOMInterfaceID* CPF_STDCALL newGOMInterfaceID(PyObject *arg)
{
	(void)arg;
	PyObject_GOMInterfaceID *self;
	self = PyObject_New(PyObject_GOMInterfaceID, &GOMInterfaceID_type);
	if (self == nullptr)
		return nullptr;
	self->mID = GOM::InterfaceID(0);
	return self;
}

//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMInterfaceID_get_id(PyObject_GOMInterfaceID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMInterfaceID_set_id(PyObject_GOMInterfaceID* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLongLong(value);
	self->mID = GOM::InterfaceID(v);
	return 0;
}

PyGetSetDef GOMInterfaceID_getseters[] =
{
	{ "id", (getter)GOMInterfaceID_get_id, (setter)GOMInterfaceID_set_id, nullptr, nullptr },
	{ NULL }
};
#endif

//////////////////////////////////////////////////////////////////////////
PyMODINIT_FUNC CPF_STDCALL PyInit_cpf()
{
	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return m;

	PyObject* mgom = PyModule_Create(&CpfGomModuleDef);
	if (mgom == nullptr)
	{
		Py_DECREF(m);
		return mgom;
	}
	PyModule_AddObject(m, "gom", mgom);

	GOMResult_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMResult_type) < 0)
		return nullptr;
	Py_INCREF(&GOMResult_type);
	PyModule_AddObject(mgom, "Result", reinterpret_cast<PyObject*>(&GOMResult_type));

	GOMClassID_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMClassID_type) < 0)
		return nullptr;
	Py_INCREF(&GOMClassID_type);
	PyModule_AddObject(m, "ClassID", reinterpret_cast<PyObject*>(&GOMClassID_type));

	GOMInterfaceID_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMInterfaceID_type) < 0)
		return nullptr;
	Py_INCREF(&GOMInterfaceID_type);
	PyModule_AddObject(m, "InterfaceID", reinterpret_cast<PyObject*>(&GOMInterfaceID_type));

	PluginRegistry_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PluginRegistry_type) < 0)
		return nullptr;
	Py_INCREF(&PluginRegistry_type);
	PyModule_AddObject(m, "Registry", reinterpret_cast<PyObject*>(&PluginRegistry_type));

	return m;
}

/*
 * I think that the goal is going to be centralized around rttr.
 * Describe the API's to rttr and then pass those into the script
 * component which will then break it down into appropriate bindings.
 * This will allow multiple script languages at the cost of speed,
 * but since this is intended as only being a tool only solution
 * it doesn't matter much.
 * There will be a couple exceptions such as the GOM::Result, GOM::ClassID
 * and core bits which will likely be manually wrapped for best results.
 */

bool Python3::_InitPython()
{
	// TODO: Redirect this properly to an asynchronous data sink
	// so the streams can be parsed, placed in different windows,
	// and most importantly, to the CPF_LOG system.
#ifdef CPF_DEBUG
#	if CPF_TARGET_WINDOWS
	AllocConsole();
	SetConsoleTitle("Python3");
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#	endif
#endif

	//////////////////////////////////////////////////////////////////////////
	// Create a Cpf module.
	if (PyImport_AppendInittab("cpf", &PyInit_cpf)==0)
	{
		Py_Initialize();
		return true;
	}
	return false;
}

GOM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
{
	bool pythonInit = _InitPython();
	(void)pythonInit;

	//////////////////////////////////////////////////////////////////////////
	// List out the registered iRegistry.
	CPF_LOG(Python3, Info) << "Begin rttr: *******************************************";
	for (const auto& type : rttr::type::get_types())
	{
		if (type.is_class())
		{
			if (type.get_metadata("Test").is_valid())
			{
				CPF_LOG(Python3, Info) << type.get_name();
				for (const auto& method : type.get_methods())
				{
					CPF_LOG(Python3, Info) << " :" << method.get_name() << " Args(" << method.get_parameter_infos().size() << ")";
				}
			}
		}
	}
	CPF_LOG(Python3, Info) << "End rttr:   *******************************************";
	//////////////////////////////////////////////////////////////////////////

	WString wpath;
	for (int i = 0; basePath[i] != 0; ++i)
		wpath.push_back(wchar_t(basePath[i]));
	PySys_SetPath(wpath.c_str());

	PyObject* pName = PyUnicode_DecodeFSDefault("TestPython");
	PyObject* pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != nullptr)
	{
		PyObject* pFunc = PyObject_GetAttrString(pModule, "multiply");
		if (pFunc && PyCallable_Check(pFunc))
		{
			PyObject* pArgs = PyTuple_New(2);
			PyObject* pValue = PyLong_FromLong(5);
			PyTuple_SetItem(pArgs, 0, pValue);
			pValue = PyLong_FromLong(7);
			PyTuple_SetItem(pArgs, 1, pValue);

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				CPF_LOG(Python3, Info) << "Python test result is 5*7 = " << PyLong_AsLong(pValue);
				Py_DECREF(pValue);
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Python3::Shutdown()
{
	Py_FinalizeEx();
	return GOM::kOK;
}


/*
y = gom.Result()
z = y.is_error()
print ("is_error: ", z)
print ("error: ", y.error)
y.error = 1
print ("error: ", y.error)
print ("subsystem: ", y.subsystem)
print ("value: ", y.value)
print ("success: ", cpf.succeeded(y))
print ("failed: ", cpf.failed(y))
print (dir(y))
print ("-------------------------------")
print(dir(cpf))
print ("-------------------------------")

classID = cpf.ClassID()
print ("ClassID: ", classID.id)
interfaceID = cpf.InterfaceID()
print ("InterfaceID: ", interfaceID.id)
interfaceID2 = cpf.InterfaceID('Hello')
print ("InterfaceID2: ", interfaceID2.id)

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b

    return c

'''
def test_registry():
	registry = Registry()
	result = registry.exists()
	print ("Exists: ", result)
'''
 */
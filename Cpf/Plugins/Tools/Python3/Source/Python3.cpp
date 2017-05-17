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
}


static PyModuleDef cpfModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf",
	"Core module integration with the Cpf frameworks.",
	-1,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

struct PythonRegistry
{
	PyObject_HEAD
	int64_t mTest;
};

static PyTypeObject cpfRegistryType =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.Registry",            /* tp_name */
	sizeof(PythonRegistry),	   /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,        /* tp_flags */
	"Cpf objects",				/* tp_doc */
};

PyMODINIT_FUNC PyInit_cpf()
{
	cpfRegistryType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&cpfRegistryType) < 0)
		return nullptr;

	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return m;

	Py_INCREF(&cpfRegistryType);
	PyModule_AddObject(m, "Registry", reinterpret_cast<PyObject*>(&cpfRegistryType));

	return m;
}


//////////////////////////////////////////////////////////////////////////
/* Xxo objects */
struct PyObject_GOMResult
{
	PyObject_HEAD
	GOM::Result mResult;
};

extern "C" void Dealloc_GOMResult(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

extern "C" PyObject* GOMResult_GetAttr(PyObject_GOMResult* self, char* name)
{
	if (strcmp(name, "error") == 0)
	{
		int value = self->mResult.Error;
		return PyLong_FromLong(value);
	}
	if (strcmp(name, "subsystem") == 0)
	{
		int value = self->mResult.SubSystem;
		return PyLong_FromLong(value);
	}
	if (strcmp(name, "value") == 0)
	{
		int value = self->mResult.Value;
		return PyLong_FromLong(value);
	}
	return nullptr;
}

extern "C" void GOMResult_SetAttr(PyObject_GOMResult* self, char *name, PyObject *v){	int value = PyLong_AsLong(v);	if (strcmp(name, "error") == 0)	{
		self->mResult.Error = value == 0 ? 0 : 1;
	}
	else if (strcmp(name, "subsystem") == 0)
	{
		self->mResult.SubSystem = value;
	}
	else if (strcmp(name, "value") == 0)
	{
		self->mResult.Value = value;
	}}

extern PyMethodDef GOMResult_methods[];

static PyTypeObject GOMResult_Type =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"xx.Result",					/*tp_name*/
	sizeof(PyObject_GOMResult),		/*tp_basicsize*/
	0,								/*tp_itemsize*/
									/* methods */
	(destructor)Dealloc_GOMResult,	/*tp_dealloc*/
	0,								/*tp_print*/
	(getattrfunc)GOMResult_GetAttr,	/*tp_getattr*/
	(setattrfunc)GOMResult_SetAttr,	/*tp_setattr*/
	0,								/*tp_reserved*/
	0,								/*tp_repr*/
	0,								/*tp_as_number*/
	0,								/*tp_as_sequence*/
	0,								/*tp_as_mapping*/
	0,								/*tp_hash*/
	0,								/*tp_call*/
	0,								/*tp_str*/
	nullptr,						/*tp_getattro*/
	0,								/*tp_setattro*/
	0,								/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,				/*tp_flags*/
	0,								/*tp_doc*/
	0,								/*tp_traverse*/
	0,								/*tp_clear*/
	0,								/*tp_richcompare*/
	0,								/*tp_weaklistoffset*/
	0,								/*tp_iter*/
	0,								/*tp_iternext*/
	GOMResult_methods,				/*tp_methods*/
	0,								/*tp_members*/
	0,								/*tp_getset*/
	0,								/*tp_base*/
	0,								/*tp_dict*/
	0,								/*tp_descr_get*/
	0,								/*tp_descr_set*/
	0,								/*tp_dictoffset*/
	0,								/*tp_init*/
	0,								/*tp_alloc*/
	0,								/*tp_new*/
	0,								/*tp_free*/
	0,								/*tp_is_gc*/
};

#define GOMResult_Check(v)      (Py_TYPE(v) == &GOMResult_Type)

extern "C" PyObject_GOMResult* newGOMResult(PyObject *arg)
{
	PyObject_GOMResult *self;
	self = PyObject_New(PyObject_GOMResult, &GOMResult_Type);
	if (self == nullptr)
		return nullptr;
	self->mResult = GOM::kOK;
	return self;
}

/* PyObject_GOMResult methods */
extern "C" PyObject* GOMResult_Succeeded(PyObject_GOMResult* self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, ":succeeded"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error == 0);
}

extern "C" PyObject* GOMResult_Failed(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":failed"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error != 0);
}

extern "C" PyObject* GOMResult_IsError(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_error"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error == 0);
}

extern "C" PyObject* GOMResult_IsSuccess(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_success"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error != 1);
}

extern "C" PyObject* GOMResult_Subsystem(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":subsystem"))
		return nullptr;
	return PyLong_FromLong(self->mResult.SubSystem);
}

extern "C" PyObject* GOMResult_Value(PyObject_GOMResult* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":value"))
		return nullptr;
	return PyLong_FromLong(self->mResult.Value);
}

PyMethodDef GOMResult_methods[] =
{
	{"succeeded", (PyCFunction)GOMResult_Succeeded,  METH_VARARGS, PyDoc_STR("Check that a result is a success code.")},
	{"failed", (PyCFunction)GOMResult_Failed,  METH_VARARGS, PyDoc_STR("Check that a result is a failure code.")},
	{"is_error", (PyCFunction)GOMResult_IsError, METH_VARARGS, PyDoc_STR("")},
	{"is_success", (PyCFunction)GOMResult_IsSuccess, METH_VARARGS, PyDoc_STR("")},
	{nullptr, nullptr}
};
/* --------------------------------------------------------------------- */

/* Function of two integers returning integer */

PyDoc_STRVAR(xx_foo_doc, "foo(i,j) Return the sum of i and j.");

extern "C" PyObject* xx_foo(PyObject *self, PyObject *args)
{
	long i, j;
	long res;
	if (!PyArg_ParseTuple(args, "ll:foo", &i, &j))
		return NULL;
	res = i + j; /* XXX Do something here */
	return PyLong_FromLong(res);
}


/* Function of no arguments returning new Xxo object */

extern "C" PyObject* xx_new(PyObject *self, PyObject *args)
{
	PyObject_GOMResult *rv;

	if (!PyArg_ParseTuple(args, ":new"))
		return NULL;
	rv = newGOMResult(args);
	if (rv == NULL)
		return NULL;
	return (PyObject *)rv;
}

/* Test bad format character */
extern "C" PyObject* xx_roj(PyObject *self, PyObject *args)
{
	PyObject *a;
	long b;
	if (!PyArg_ParseTuple(args, "O#:roj", &a, &b))
		return NULL;
	Py_INCREF(Py_None);
	return Py_None;
}


/* ---------- */

static PyTypeObject Str_Type =
{
	PyVarObject_HEAD_INIT(NULL, 0)
	"xxmodule.Str",						/*tp_name*/
	0,									/*tp_basicsize*/
	0,									/*tp_itemsize*/
	/* methods */
	0,									/*tp_dealloc*/
	0,									/*tp_print*/
	0,									/*tp_getattr*/
	0,									/*tp_setattr*/
	0,									/*tp_reserved*/
	0,									/*tp_repr*/
	0,									/*tp_as_number*/
	0,									/*tp_as_sequence*/
	0,									/*tp_as_mapping*/
	0,									/*tp_hash*/
	0,									/*tp_call*/
	0,									/*tp_str*/
	0,									/*tp_getattro*/
	0,									/*tp_setattro*/
	0,									/*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	0,									/*tp_doc*/
	0,									/*tp_traverse*/
	0,									/*tp_clear*/
	0,									/*tp_richcompare*/
	0,									/*tp_weaklistoffset*/
	0,									/*tp_iter*/
	0,									/*tp_iternext*/
	0,									/*tp_methods*/
	0,									/*tp_members*/
	0,									/*tp_getset*/
	0, /* see PyInit_xx */				/*tp_base*/
	0,									/*tp_dict*/
	0,									/*tp_descr_get*/
	0,									/*tp_descr_set*/
	0,									/*tp_dictoffset*/
	0,									/*tp_init*/
	0,									/*tp_alloc*/
	0,									/*tp_new*/
	0,									/*tp_free*/
	0,									/*tp_is_gc*/
};


// Functions to be exposed in the cpf.gom module.
/* create_result(error, subsystem, desc)
 * success(cpf.gom.result)
 * failed(cpf.gom.result)
 * -- Failure codes from GOM/Result.hpp
 */

/* List of functions defined in the module */

PyMethodDef xx_methods[] =
{
	{ "roj", xx_roj, METH_VARARGS, PyDoc_STR("roj(a,b) -> None") },
	{ "foo", xx_foo, METH_VARARGS, xx_foo_doc },
	{ "new", xx_new, METH_VARARGS, PyDoc_STR("new() -> new Xx object") },
	{ NULL, NULL }
};

PyDoc_STRVAR(module_doc, "This is a template module just for instruction.");

// TODO: Keeping as an example for the moment.
static PyObject *ErrorObject;


extern "C" int xx_exec(PyObject *m)
{
	/* Due to cross platform compiler issues the slots must be filled
	* here. It's required for portability to Windows without requiring
	* C++. */
	Str_Type.tp_base = &PyUnicode_Type;

	/* Finalize the type object including setting type of the new type
	* object; doing it here is required for portability, too. */
	if (PyType_Ready(&GOMResult_Type) < 0)
		goto fail;
	PyModule_AddObject(m, "Result", (PyObject*)&GOMResult_Type);

	/* Add some symbolic constants to the module */
	if (ErrorObject == NULL)
	{
		ErrorObject = PyErr_NewException("xx.error", NULL, NULL);
		if (ErrorObject == NULL)
			goto fail;
	}
	Py_INCREF(ErrorObject);
	PyModule_AddObject(m, "error", ErrorObject);

	/* Add Str */
	if (PyType_Ready(&Str_Type) < 0)
		goto fail;
	PyModule_AddObject(m, "Str", (PyObject *)&Str_Type);

	return 0;
fail:
	Py_XDECREF(m);
	return -1;
}

struct PyModuleDef_Slot xx_slots[] =
{
	{ Py_mod_exec, xx_exec },
	{ 0, NULL },
};

struct PyModuleDef xxmodule =
{
	PyModuleDef_HEAD_INIT,
	"xx",
	module_doc,
	0,
	xx_methods,
	xx_slots,
	NULL,
	NULL,
	NULL
};

/* Export function for the module (*must* be called PyInit_xx) */

PyMODINIT_FUNC PyInit_xx()
{
	return PyModuleDef_Init(&xxmodule);
}
//////////////////////////////////////////////////////////////////////////

/*
 * I think that the goal is going to be centralized around rttr.
 * Describe the API's to rttr and then pass those into the script
 * component which will then break it down into appropriate bindings.
 * This will allow multiple script languages at the cost of speed,
 * but since this is intended as only being a tool only solution
 * it doesn't matter much.
 */

GOM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
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
	PyImport_AppendInittab("cpf", &PyInit_cpf);
	PyImport_AppendInittab("xx", &PyInit_xx);
	Py_Initialize();


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

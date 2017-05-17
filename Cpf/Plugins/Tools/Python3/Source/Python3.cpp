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

extern PyMethodDef GOMResult_methods[];
extern PyGetSetDef GOMResult_getseters[];

static PyTypeObject GOMResult_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.Result",				/* tp_name */
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
};

PyMODINIT_FUNC CPF_STDCALL PyInit_cpf()
{
	GOMResult_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMResult_type) < 0)
		return nullptr;

	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return m;

	Py_INCREF(&GOMResult_type);
	PyModule_AddObject(m, "Result", reinterpret_cast<PyObject*>(&GOMResult_type));

	return m;
}


//////////////////////////////////////////////////////////////////////////
extern "C" void CPF_STDCALL Dealloc_GOMResult(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

extern "C" PyObject* CPF_STDCALL GOMResult_GetAttr(PyObject_GOMResult* self, char* name)
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

extern "C" void CPF_STDCALL GOMResult_SetAttr(PyObject_GOMResult* self, char *name, PyObject *v)
{
	int value = PyLong_AsLong(v);
	if (strcmp(name, "error") == 0)
	{
		self->mResult.Error = value == 0 ? 0 : 1;
	}
	else if (strcmp(name, "subsystem") == 0)
	{
		self->mResult.SubSystem = value;
	}
	else if (strcmp(name, "value") == 0)
	{
		self->mResult.Value = value;
	}
}

#define GOMResult_Check(v)      (Py_TYPE(v) == &GOMResult_type)

extern "C" PyObject_GOMResult* CPF_STDCALL newGOMResult(PyObject *arg)
{
	(void)arg;
	PyObject_GOMResult *self;
	self = PyObject_New(PyObject_GOMResult, &GOMResult_type);
	if (self == nullptr)
		return nullptr;
	self->mResult = GOM::kOK;
	return self;
}

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

extern "C" PyObject* CPF_STDCALL GOMResult_get_subsystem(PyObject_GOMResult* self, void*)
{
	return PyLong_FromLong(self->mResult.SubSystem);
}

extern "C" PyObject* CPF_STDCALL GOMResult_get_value(PyObject_GOMResult* self, void*)
{
	return PyLong_FromLong(self->mResult.Value);
}

PyGetSetDef GOMResult_getseters[] =
{
	{ "error", (getter)GOMResult_get_error, NULL, NULL, NULL },
	{ "subsystem", (getter)GOMResult_get_subsystem, NULL, NULL, NULL },
	{ "value", (getter)GOMResult_get_value, NULL, NULL, NULL },
	{ NULL }
};


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

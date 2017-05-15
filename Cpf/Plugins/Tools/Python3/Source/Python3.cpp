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

COM::Result CPF_STDCALL Python3::QueryInterface(COM::InterfaceID id, void** outIface)
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
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
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


/*
 * I think that the goal is going to be centralized around rttr.
 * Describe the API's to rttr and then pass those into the script
 * component which will then break it down into appropriate bindings.
 * This will allow multiple script languages at the cost of speed,
 * but since this is intended as only being a tool only solution
 * it doesn't matter much.
 */

COM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
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
	return COM::kOK;
}

COM::Result CPF_STDCALL Python3::Shutdown()
{
	Py_FinalizeEx();
	return COM::kOK;
}

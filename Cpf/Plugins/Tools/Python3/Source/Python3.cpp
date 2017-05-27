//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include "rttr/registration.h"
#include "Plugin/iRegistry.hpp"
#include "GOM/pyModule.hpp"
#include "GOM/pyResult.hpp"
#include "Plugin/pyModule.hpp"

using namespace Cpf;
using namespace Tools;

Python3* s_Python3 = nullptr;

Python3::Python3(iBase*)
	: mpCreateRegistry(nullptr)
{
	s_Python3 = this;
}

Python3::~Python3()
{
	s_Python3 = nullptr;
}

GOM::Result CPF_STDCALL Python3::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
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


//////////////////////////////////////////////////////////////////////////
PyMethodDef Cpf_methods[];
static PyModuleDef cpfModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf",
	"Core module integration with the Cpf frameworks.",
	-1,
	Cpf_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

extern "C" PyObject* CPF_STDCALL CpfCrc15(PyObject*, PyObject* args)
{
	char* strValue = nullptr;
	if (!PyArg_ParseTuple(args, "s:crc15", &strValue))
		return nullptr;
	return PyLong_FromLong(Hash::Crc15(strValue, ::strlen(strValue)));
}

extern "C" PyObject* CPF_STDCALL CpfCrc16(PyObject*, PyObject* args)
{
	char* strValue = nullptr;
	if (!PyArg_ParseTuple(args, "s:crc16", &strValue))
		return nullptr;
	return PyLong_FromLong(Hash::Crc16(strValue, ::strlen(strValue)));
}

extern "C" PyObject* CPF_STDCALL CpfCrc32(PyObject*, PyObject* args)
{
	char* strValue = nullptr;
	if (!PyArg_ParseTuple(args, "s:crc32", &strValue))
		return nullptr;
	return PyLong_FromLong(Hash::Crc32(strValue, ::strlen(strValue)));
}

extern "C" PyObject* CPF_STDCALL CpfCrc64(PyObject*, PyObject* args)
{
	char* strValue = nullptr;
	if (!PyArg_ParseTuple(args, "s:crc64", &strValue))
		return nullptr;
	return PyLong_FromLongLong(Hash::Crc64(strValue, ::strlen(strValue)));
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef Cpf_methods[] =
{
	{ "crc15", (PyCFunction)CpfCrc15, METH_VARARGS, PyDoc_STR("Compute the crc15 of the given string.") },
	{ "crc16", (PyCFunction)CpfCrc16, METH_VARARGS, PyDoc_STR("Compute the crc16 of the given string.") },
	{ "crc32", (PyCFunction)CpfCrc32, METH_VARARGS, PyDoc_STR("Compute the crc32 of the given string.") },
	{ "crc64", (PyCFunction)CpfCrc64, METH_VARARGS, PyDoc_STR("Compute the crc64 of the given string.") },
	{ nullptr, nullptr }
};


PyMODINIT_FUNC CPF_STDCALL PyInit_cpf()
{
	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return nullptr;

	if (GOM::py::AddModule(m) &&
		Plugin::py::AddModule(m))
	{
		return m;
	}

	return nullptr;
}

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

GOM::Result CPF_STDCALL Python3::Initialize(const char* basePath, CreateRegistryPtr createRegistry)
{
	mpCreateRegistry = createRegistry;
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

	// Run the gom tests.
	{
		PyObject* pName = PyUnicode_DecodeFSDefault("test_gom");
		PyObject* testGom = PyImport_Import(pName);
		if (testGom)
		{
			PyObject* pFunc = PyObject_GetAttrString(testGom, "run_tests");
			if (pFunc && PyCallable_Check(pFunc))
			{
				PyObject_CallObject(pFunc, nullptr);
			}
		}
		Py_DECREF(pName);
		Py_DECREF(testGom);
	}
	if (PyErr_Occurred())
		PyErr_Print();
	{
		// Run the plugin tests.
		PyObject* pName = PyUnicode_DecodeFSDefault("test_plugin");
		PyObject* testPlugin = PyImport_Import(pName);
		if (testPlugin)
		{
			PyObject* pFunc = PyObject_GetAttrString(testPlugin, "run_tests");
			if (pFunc && PyCallable_Check(pFunc))
			{
				PyObject_CallObject(pFunc, nullptr);
			}
		}
		Py_DECREF(pName);
		Py_DECREF(testPlugin);
	}
	if (PyErr_Occurred())
		PyErr_Print();

	return GOM::kOK;
}

GOM::Result CPF_STDCALL Python3::Shutdown()
{
	Py_FinalizeEx();
	return GOM::kOK;
}

GOM::Result Python3::CreateRegistry(Plugin::iRegistry** reg) const
{
	return (*mpCreateRegistry)(reg);
}

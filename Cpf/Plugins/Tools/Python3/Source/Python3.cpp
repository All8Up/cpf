//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include "Plugin/iRegistry.hpp"
#include <Python.h>

using namespace Cpf;
using namespace Tools;

Python3* s_Python3 = nullptr;

Python3::Python3(iUnknown*)
	: mpCreateRegistry(nullptr)
{
	s_Python3 = this;
}

Python3::~Python3()
{
	s_Python3 = nullptr;
}

GOM::Result CPF_STDCALL Python3::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
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

extern "C" PyObject* CPF_STDCALL CreateRegistry(PyObject*, PyObject*)
{
	if (s_Python3)
	{
		Plugin::iRegistry* regy = nullptr;
		if (GOM::Succeeded(s_Python3->CreateRegistry(&regy)))
		{
			return PyCapsule_New(regy, nullptr, [](PyObject* obj)
			{
				auto base = reinterpret_cast<GOM::iUnknown*>(PyCapsule_GetPointer(obj, nullptr));
				base->Release();
			});
		}
	}
	return nullptr;
}

extern "C" CPF_EXPORT void CpfCreateRegistry(void** regy)
{
	if (s_Python3)
	{
		Plugin::iRegistry* result = nullptr;
		if (GOM::Succeeded(s_Python3->CreateRegistry(&result)))
			*regy = result;
		else
			*regy = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef Cpf_methods[] =
{
	{ "crc15", (PyCFunction)CpfCrc15, METH_VARARGS, PyDoc_STR("Compute the crc15 of the given string.") },
	{ "crc16", (PyCFunction)CpfCrc16, METH_VARARGS, PyDoc_STR("Compute the crc16 of the given string.") },
	{ "crc32", (PyCFunction)CpfCrc32, METH_VARARGS, PyDoc_STR("Compute the crc32 of the given string.") },
	{ "crc64", (PyCFunction)CpfCrc64, METH_VARARGS, PyDoc_STR("Compute the crc64 of the given string.") },
	{ "create_registry", (PyCFunction)CreateRegistry, METH_VARARGS, PyDoc_STR("Create a registry instance.") },
	{ nullptr, nullptr }
};

static PyModuleDef cpfModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpfcore",
	"Core module integration with the Cpf frameworks.",
	-1,
	Cpf_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

PyMODINIT_FUNC CPF_STDCALL PyInit_cpf()
{
	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return nullptr;
	return m;
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
	if (PyImport_AppendInittab("cpfcore", &PyInit_cpf)==0)
	{
		Py_Initialize();
		if (!PyEval_ThreadsInitialized())
		{
			PyEval_InitThreads();

			wchar_t* args[] = {L""};
			PySys_SetArgv(1, args);
		}
		return true;
	}
	return false;
}

GOM::Result CPF_STDCALL Python3::Initialize(const char* basePath, CreateRegistryPtr createRegistry)
{
	mpCreateRegistry = createRegistry;
	bool pythonInit = _InitPython();
	(void)pythonInit;

	// Setup the extended path.
	char buffer[1024];
	::strcpy(buffer,
		"import sys\n"
		"sys.path.append(\""
	);
	::strcat(buffer, basePath);
	::strcat(buffer, "networked/");
	::strcat(buffer, "\")\n");

	::strcat(buffer, "sys.path.append(\"");
	::strcat(buffer, basePath);
	::strcat(buffer, "plugins/py\")\n");

	PyRun_SimpleString(buffer);
	if (PyErr_Occurred())
		PyErr_Print();

	// Run the integration tests.
	{
		PyObject* pName = PyUnicode_DecodeFSDefault("test_integration");
		PyObject* tesetIntegration = PyImport_Import(pName);
		if (tesetIntegration)
			Py_DECREF(tesetIntegration);
		Py_DECREF(pName);
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

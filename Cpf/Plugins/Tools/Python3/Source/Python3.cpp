//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include "rttr/registration.h"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "GOM/pyModule.hpp"
#include "GOM/pyResult.hpp"
#include "Plugin/pyModule.hpp"

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
		.method("GetInstance", &Plugin::iRegistry::GetInstances)
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
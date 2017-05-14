//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include <Python.h>

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



/* Return the number of arguments of the application command line */
static int numargs = 0;

static PyObject*
emb_numargs(PyObject*, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":numargs"))
		return NULL;
	return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
	{ "numargs", emb_numargs, METH_VARARGS,
	"Return the number of arguments received by the process." },
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "cpf", NULL, -1, EmbMethods,
	NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb()
{
	return PyModule_Create(&EmbModule);
}

COM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
{
	numargs = 5;
	PyImport_AppendInittab("cpf", &PyInit_emb);
	Py_Initialize();

	WString wpath;
	for (int i = 0; basePath[i] != 0; ++i)
		wpath.push_back(wchar_t(basePath[i]));
	PySys_SetPath(wpath.c_str());

	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	pName = PyUnicode_DecodeFSDefault("TestPython");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule!=nullptr)
	{
		pFunc = PyObject_GetAttrString(pModule, "multiply");
		if (pFunc && PyCallable_Check(pFunc))
		{
			pArgs = PyTuple_New(2);
			pValue = PyLong_FromLong(5);
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

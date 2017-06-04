//////////////////////////////////////////////////////////////////////////
#include "GOM/pyMethods.hpp"
#include "GOM/pyResult.hpp"
#include "GOM/iBase.hpp"

using namespace Cpf;


extern "C" PyObject* CPF_STDCALL CpfGOMSucceeded(GOM::py::Result*, PyObject* args)
{
	GOM::py::Result* result;
	if (!PyArg_ParseTuple(args, "O:succeeded", &result))
		return nullptr;
	return PyBool_FromLong(result->mResult.Error == 0);
}

extern "C" PyObject* CPF_STDCALL CpfGOMFailed(GOM::py::Result*, PyObject* args)
{
	GOM::py::Result* result;
	if (!PyArg_ParseTuple(args, "O:failed", &result))
		return nullptr;
	return PyBool_FromLong(result->mResult.Error != 0);
}

extern "C" PyObject* CPF_STDCALL CpfGOMAddRef(PyObject*, PyObject* args)
{
	PyObject* capsule = nullptr;
	if (!PyArg_ParseTuple(args, "O:add_ref", &capsule))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	GOM::iBase* base = reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(capsule, nullptr));
	if (base)
	{
		base->AddRef();
		Py_RETURN_NONE;
	}

	PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
	return nullptr;
}
extern "C" PyObject* CPF_STDCALL CpfGOMRelease(PyObject*, PyObject* args)
{
	PyObject* capsule = nullptr;
	if (!PyArg_ParseTuple(args, "O:release", &capsule))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	GOM::iBase* base = reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(capsule, nullptr));
	if (base)
	{
		base->Release();
		Py_RETURN_NONE;
	}

	PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef GOM::py::CpfGOM_methods[] =
{
	{ "succeeded", (PyCFunction)CpfGOMSucceeded, METH_VARARGS, PyDoc_STR("Determine if a call succeeded.") },
	{ "failed", (PyCFunction)CpfGOMFailed, METH_VARARGS, PyDoc_STR("Determine if a call failed.") },
	{ "add_ref", (PyCFunction)CpfGOMAddRef, METH_VARARGS, PyDoc_STR("Add a reference to a pointer.") },
	{ "release", (PyCFunction)CpfGOMRelease, METH_VARARGS, PyDoc_STR("Remove a reference to a pointer.") },
	{ nullptr, nullptr }
};

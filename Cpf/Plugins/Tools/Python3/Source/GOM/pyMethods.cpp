//////////////////////////////////////////////////////////////////////////
#include "GOM/pyMethods.hpp"
#include "GOM/pyResult.hpp"

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

//////////////////////////////////////////////////////////////////////////
PyMethodDef GOM::py::CpfGOM_methods[] =
{
	{ "succeeded", (PyCFunction)CpfGOMSucceeded, METH_VARARGS, PyDoc_STR("Determine if a call succeeded.") },
	{ "failed", (PyCFunction)CpfGOMFailed, METH_VARARGS, PyDoc_STR("Determine if a call failed.") },
	{ nullptr, nullptr }
};

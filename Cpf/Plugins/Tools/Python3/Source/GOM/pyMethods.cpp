//////////////////////////////////////////////////////////////////////////
#include "GOM/pyMethods.hpp"
#include "GOM/pyResult.hpp"
#include "GOM/iBase.hpp"
#include "GOM/pyInterfaceID.hpp"
#include "GOM/pyClassID.hpp"

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
extern "C" PyObject* CPF_STDCALL CpfGOMCast(PyObject*, PyObject* args)
{
	// Returns the capsule for the desired iid, or throws an exception on failure.
	PyObject* capsule = nullptr;
	PyObject* iid = nullptr;
	if (!PyArg_ParseTuple(args, "OO:cast", &capsule, &iid))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	if (!GOMInterfaceID_Check(iid) || !PyCapsule_CheckExact(capsule))
	{
		PyErr_SetString(PyExc_RuntimeError, "Invalid argument.");
		return nullptr;
	}
	GOM::iBase* base = reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(capsule, nullptr));
	if (base)
	{
		GOM::py::InterfaceID* iface = reinterpret_cast<GOM::py::InterfaceID*>(iid);
		void* result = nullptr;
		if (Succeeded(base->Cast(iface->mID, &result)))
		{
			if (result==base)
			{
				base->Release();
				Py_INCREF(capsule);
				return capsule;
			}
			PyObject* resCap = PyCapsule_New(result, nullptr, [](PyObject* obj)
			{
				auto iface = reinterpret_cast<GOM::iBase*>(PyCapsule_GetPointer(obj, nullptr));
				iface->Release();
			});
			return resCap;
		}
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
	{ "cast", (PyCFunction)CpfGOMCast, METH_VARARGS, PyDoc_STR("Cast to the given interface.") },
	{ nullptr, nullptr }
};

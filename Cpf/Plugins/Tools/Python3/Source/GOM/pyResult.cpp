//////////////////////////////////////////////////////////////////////////
#include "GOM/pyResult.hpp"
#include "Configuration.hpp"
#include "Hash/Crc.hpp"

using namespace Cpf;
using namespace GOM;

extern "C" int CPF_STDCALL ResultInit(py::Result* self, PyObject* args, PyObject* kwds)
{
	int error = 0;
	char* subSys = nullptr;
	char* value = nullptr;
	self->mResult = Result{ 0, 0, 0 };
	char* keys[] = { "error", "subsystem", "value" };
	
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iss", keys, &error, &subSys, &value))
	{
		return -1;
	}
	if (subSys && value)
		self->mResult = Result{ uint32_t(error == 0 ? 0 : 1), Hash::Crc16(subSys, ::strlen(subSys)), Hash::Crc15(value, ::strlen(value)) };
	return 0;
}

extern "C" void CPF_STDCALL ResultFree(py::Result *self)
{
	PyObject_Del(self);
}

#define GOMResult_Check(v)      (Py_TYPE(v) == &GOMResult_type)

/* PyObject_GOMResult methods */
extern "C" PyObject* CPF_STDCALL ResultIsSuccess(py::Result* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_success"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error == 0);
}

extern "C" PyObject* CPF_STDCALL ResultIsError(py::Result* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":is_error"))
		return nullptr;
	return PyBool_FromLong(self->mResult.Error != 0);
}


//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL ResultGetError(py::Result* self, void*)
{
	return PyLong_FromLong(self->mResult.Error);
}

extern "C" int CPF_STDCALL ResultSetError(py::Result* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.Error = v;
	return 0;
}

extern "C" PyObject* CPF_STDCALL ResultGetSubSystem(py::Result* self, void*)
{
	return PyLong_FromLong(self->mResult.SubSystem);
}

extern "C" int CPF_STDCALL ResultSetSubSystem(py::Result* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.SubSystem = v;
	return 0;
}

extern "C" PyObject* CPF_STDCALL ResultGetValue(py::Result* self, void*)
{
	return PyLong_FromLong(self->mResult.Value);
}

extern "C" int CPF_STDCALL ResultSetValue(py::Result* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLong(value);
	self->mResult.Value = v;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
PyMethodDef GOMResult_methods[] =
{
	{ "is_error", (PyCFunction)ResultIsError, METH_VARARGS, PyDoc_STR("Determine if the result indicates an error occurred.") },
	{ "is_success", (PyCFunction)ResultIsSuccess, METH_VARARGS, PyDoc_STR("Determine if the result indicates success.") },
	{ nullptr, nullptr }
};

PyGetSetDef GOMResult_getseters[] =
{
	{ "error", (getter)ResultGetError, (setter)ResultSetError, nullptr, nullptr },
	{ "subsystem", (getter)ResultGetSubSystem, (setter)ResultSetSubSystem, NULL, NULL },
	{ "value", (getter)ResultGetValue, (setter)ResultSetValue, NULL, NULL },
	{ NULL }
};


//////////////////////////////////////////////////////////////////////////
static PyTypeObject GOMResult_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.Result",					/* tp_name */
	sizeof(py::Result),				/* tp_basicsize */
	0,								/* tp_itemsize */
	(destructor)ResultFree,			/* tp_dealloc */
	nullptr,						/* tp_print */
	nullptr,						/* tp_getattr */
	nullptr,						/* tp_setattr */
	nullptr,						/* tp_reserved */
	nullptr,						/* tp_repr */
	nullptr,						/* tp_as_number */
	nullptr,						/* tp_as_sequence */
	nullptr,						/* tp_as_mapping */
	nullptr,						/* tp_hash  */
	nullptr,						/* tp_call */
	nullptr,						/* tp_str */
	nullptr,						/* tp_getattro */
	nullptr,						/* tp_setattro */
	nullptr,						/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,				/* tp_flags */
	"Cpf objects",					/* tp_doc */
	nullptr,						/* tp_traverse */
	nullptr,						/* tp_clear */
	nullptr,						/* tp_richcompare */
	0,								/* tp_weaklistoffset */
	nullptr,						/* tp_iter */
	nullptr,						/* tp_iternext */
	GOMResult_methods,				/* tp_methods */
	nullptr,						/* tp_members */
	GOMResult_getseters,			/* tp_getset */
	nullptr,						/* tp_base */
	nullptr,						/* tp_dict */
	nullptr,						/* tp_descr_get */
	nullptr,						/* tp_descr_set */
	0,								/* tp_dictoffset */
	(initproc)ResultInit,			/* tp_init */
	nullptr,						/* tp_alloc */
	nullptr,						/* tp_new */
	nullptr,						/* tp_free */
	nullptr,						/* tp_is_gc */
	nullptr,						/* tp_bases */
	nullptr,						/* tp_mro */
	nullptr,						/* tp_cache */
	nullptr,						/* tp_subclasses */
	nullptr,						/* tp_weaklist */
	nullptr,						/* tp_del */
	0,								/* tp_version_tag */
	nullptr							/* tp_finalize */
}; 


bool AddResultCode(PyObject* parent, const char* name, Result code)
{
	py::Result* result = PyObject_New(py::Result, &GOMResult_type);
	if (result)
	{
		result->mResult = code;
		PyModule_AddObject(parent, name, reinterpret_cast<PyObject*>(result));
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool py::AddResultType(PyObject* parent)
{
	GOMResult_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMResult_type) < 0)
		return false;
	Py_INCREF(&GOMResult_type);
	PyModule_AddObject(parent, "Result", reinterpret_cast<PyObject*>(&GOMResult_type));

	if (AddResultCode(parent, "kOK", kOK) &&
		AddResultCode(parent, "kError", kError) &&
		AddResultCode(parent, "kUnknownInterface", kUnknownInterface) &&
		AddResultCode(parent, "kInvalidParameter", kInvalidParameter) &&
		AddResultCode(parent, "kOutOfMemory", kOutOfMemory) &&
		AddResultCode(parent, "kUnknownClass", kUnknownClass) &&
		AddResultCode(parent, "kNotImplemented", kNotImplemented) &&
		AddResultCode(parent, "kInvalid", kInvalid) &&
		AddResultCode(parent, "kNotEnoughSpace", kNotEnoughSpace) &&
		AddResultCode(parent, "kInUse", kInUse) &&
		AddResultCode(parent, "kNotInitialized", kNotInitialized) &&
		AddResultCode(parent, "kInitializationFailure", kInitializationFailure) &&
		AddResultCode(parent, "kOutOfRange", kOutOfRange) &&
		AddResultCode(parent, "kDuplicateCID", kDuplicateCID) &&
		AddResultCode(parent, "kRegistryError", kRegistryError) &&
		AddResultCode(parent, "kNotRunning", kNotRunning)
		)
		return true;
	return false;
}

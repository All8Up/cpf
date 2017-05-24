//////////////////////////////////////////////////////////////////////////
#include "GOM/pyBase.hpp"
#include "Configuration.hpp"

using namespace Cpf;
using namespace GOM;

extern "C" int CPF_STDCALL BaseInit(py::Base* self, PyObject* args, PyObject* kwds)
{
	(void)args; (void)kwds;
	self->mpBase = nullptr;
//	if (!PyArg_ParseTuple(args, "|:", keys, &error, &subSys, &value))
//	{
//		return -1;
//	}
	return 0;
}

extern "C" void CPF_STDCALL BaseFree(py::Base *self)
{
	PyObject_Del(self);
}

#define GOMBase_Check(v)      (Py_TYPE(v) == &GOMUnknown_type)

extern "C" PyObject* CPF_STDCALL BaseCast(py::Base* self, PyObject* args)
{
	if (!PyArg_ParseTuple(args, ":cast"))
		return nullptr;
//	if (GOMUnknown_Check(self))
	{
		
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef GOMBase_methods[] =
{
	{ "cast", (PyCFunction)BaseCast, METH_VARARGS, PyDoc_STR("Attempt to cast to the given interface.") },
	{ nullptr, nullptr }
};

PyGetSetDef GOMBase_getseters[] =
{
	{ NULL }
};


//////////////////////////////////////////////////////////////////////////
static PyTypeObject GOMBase_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.Base",						/* tp_name */
	sizeof(py::Base),				/* tp_basicsize */
	0,								/* tp_itemsize */
	(destructor)BaseFree,			/* tp_dealloc */
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
	GOMBase_methods,				/* tp_methods */
	nullptr,						/* tp_members */
	GOMBase_getseters,				/* tp_getset */
	nullptr,						/* tp_base */
	nullptr,						/* tp_dict */
	nullptr,						/* tp_descr_get */
	nullptr,						/* tp_descr_set */
	0,								/* tp_dictoffset */
	(initproc)BaseInit,				/* tp_init */
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

//////////////////////////////////////////////////////////////////////////
bool py::AddBaseType(PyObject* parent)
{
	GOMBase_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMBase_type) < 0)
		return false;
	Py_INCREF(&GOMBase_type);
	PyModule_AddObject(parent, "Unknown", reinterpret_cast<PyObject*>(&GOMBase_type));

	return true;
}

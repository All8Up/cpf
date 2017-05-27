//////////////////////////////////////////////////////////////////////////
#include "GOM/pyBase.hpp"
#include "Configuration.hpp"
#include <structmember.h>

using namespace Cpf;
using namespace GOM;

PyObject* s_pBaseID = nullptr;

extern "C" int CPF_STDCALL BaseInit(py::Base* self, PyObject* args, PyObject* kwds)
{
	(void)args; (void)kwds;
	self->mpBase = nullptr;
	self->mpIID = s_pBaseID;
//	if (!PyArg_ParseTuple(args, "|:", keys, &error, &subSys, &value))
//	{
//		return -1;
//	}
	return 0;
}

extern "C" void CPF_STDCALL BaseFree(py::Base *self)
{
	self->mpBase->Release();
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
	PyErr_SetString(PyExc_RuntimeError, "Not implemented.");
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
PyMethodDef GOMBase_methods[] =
{
	{ "cast", (PyCFunction)BaseCast, METH_VARARGS, PyDoc_STR("Attempt to cast to the given interface.") },
	{ nullptr, nullptr }
};

PyMemberDef Base_members[] =
{
	{ "iid", T_OBJECT, offsetof(py::Base, mpIID), READONLY },
	{ nullptr }
};

PyGetSetDef GOMBase_getseters[] =
{
	{ NULL }
};


//////////////////////////////////////////////////////////////////////////
PyTypeObject py::Base_type =
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
	Py_TPFLAGS_DEFAULT |
//	Py_TPFLAGS_IS_ABSTRACT |
	Py_TPFLAGS_BASETYPE,			/* tp_flags */
	"Cpf objects",					/* tp_doc */
	nullptr,						/* tp_traverse */
	nullptr,						/* tp_clear */
	nullptr,						/* tp_richcompare */
	0,								/* tp_weaklistoffset */
	nullptr,						/* tp_iter */
	nullptr,						/* tp_iternext */
	GOMBase_methods,				/* tp_methods */
	Base_members,					/* tp_members */
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
	s_pBaseID = reinterpret_cast<PyObject*>(PyObject_New(GOM::py::Base, &GOM::py::Base_type));

	Base_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&Base_type) < 0)
		return false;
	Py_INCREF(&Base_type);
	PyModule_AddObject(parent, "Base", reinterpret_cast<PyObject*>(&Base_type));

	return true;
}

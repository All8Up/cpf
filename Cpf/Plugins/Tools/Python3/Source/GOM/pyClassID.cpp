//////////////////////////////////////////////////////////////////////////
#include "GOM/pyClassID.hpp"
#include "GOM/pyResult.hpp"

using namespace Cpf;
using namespace GOM;

extern "C" int CPF_STDCALL Init_GOMClassID(py::ClassID* self, PyObject* args, PyObject*)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "|s", &name))
	{
		self->mID = ClassID(0);
		return 1;
	}
	self->mID = ClassID(name ? Hash::Crc64(name, ::strlen(name)) : 0);
	return 1;
}

extern "C" Py_hash_t CPF_STDCALL ClassIDHash(py::ClassID* self)
{
	return self->mID.GetID();
}

extern "C" PyObject* ClassIDCompare(PyObject *a, PyObject *b, int op)
{
	if (GOMClassID_Check(b))
	{
		const GOM::ClassID& lhs = reinterpret_cast<py::ClassID*>(a)->mID;
		const GOM::ClassID& rhs = reinterpret_cast<py::ClassID*>(b)->mID;
		switch (op)
		{
		case Py_LT:
			return lhs < rhs ? Py_True : Py_False;
		case Py_LE:
			return lhs <= rhs ? Py_True : Py_False;
		case Py_EQ:
			return lhs == rhs ? Py_True : Py_False;
		case Py_NE:
			return lhs != rhs ? Py_True : Py_False;
		case Py_GT:
			return lhs > rhs ? Py_True : Py_False;
		case Py_GE:
			return lhs >= rhs ? Py_True : Py_False;
		default:
			break;
		}
	}
	return PyExc_TypeError;
}

//////////////////////////////////////////////////////////////////////////
extern PyGetSetDef GOMClassID_getseters[];

PyTypeObject py::ClassID_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.ClassID",				/* tp_name */
	sizeof(py::ClassID),		/* tp_basicsize */
	0,							/* tp_itemsize */
	nullptr,					/* tp_dealloc */
	nullptr,					/* tp_print */
	nullptr,					/* tp_getattr */
	nullptr,					/* tp_setattr */
	nullptr,					/* tp_reserved */
	nullptr,					/* tp_repr */
	nullptr,					/* tp_as_number */
	nullptr,					/* tp_as_sequence */
	nullptr,					/* tp_as_mapping */
	(hashfunc)ClassIDHash,		/* tp_hash  */
	nullptr,					/* tp_call */
	nullptr,					/* tp_str */
	nullptr,					/* tp_getattro */
	nullptr,					/* tp_setattro */
	nullptr,					/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,			/* tp_flags */
	"Cpf objects",				/* tp_doc */
	nullptr,					/* tp_traverse */
	nullptr,					/* tp_clear */
	ClassIDCompare,				/* tp_richcompare */
	0,							/* tp_weaklistoffset */
	nullptr,					/* tp_iter */
	nullptr,					/* tp_iternext */
	nullptr,					/* tp_methods */
	nullptr,					/* tp_members */
	GOMClassID_getseters,		/* tp_getset */
	nullptr,					/* tp_base */
	nullptr,					/* tp_dict */
	nullptr,					/* tp_descr_get */
	nullptr,					/* tp_descr_set */
	0,							/* tp_dictoffset */
	(initproc)Init_GOMClassID,	/* tp_init */
	nullptr,					/* tp_alloc */
	nullptr,					/* tp_new */
	nullptr,					/* tp_free */
	nullptr,					/* tp_is_gc */
	nullptr,					/* tp_bases */
	nullptr,					/* tp_mro */
	nullptr,					/* tp_cache */
	nullptr,					/* tp_subclasses */
	nullptr,					/* tp_weaklist */
	nullptr,					/* tp_del */
	0,							/* tp_version_tag */
	nullptr						/* tp_finalize */
};

extern "C" void CPF_STDCALL Dealloc_GOMClassID(py::Result *self)
{
	PyObject_Del(self);
}



//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMClassID_get_id(py::ClassID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMClassID_set_id(py::ClassID* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLongLong(value);
	self->mID = ClassID(v);
	return 0;
}

PyGetSetDef GOMClassID_getseters[] =
{
	{ "id", (getter)GOMClassID_get_id, (setter)GOMClassID_set_id, nullptr, nullptr },
	{ NULL }
};

//////////////////////////////////////////////////////////////////////////
bool py::AddClassIDType(PyObject* parent)
{
	ClassID_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&ClassID_type) < 0)
		return false;
	Py_INCREF(&ClassID_type);
	PyModule_AddObject(parent, "ClassID", reinterpret_cast<PyObject*>(&ClassID_type));

	return true;
}

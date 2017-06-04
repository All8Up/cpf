//////////////////////////////////////////////////////////////////////////
#include "GOM/pyInterfaceID.hpp"
#include "GOM/pyResult.hpp"

using namespace Cpf;
using namespace GOM;

extern "C" int CPF_STDCALL Init_InterfaceID(py::InterfaceID* self, PyObject* args, PyObject*)
{
	char* name = nullptr;
	if (PyArg_ParseTuple(args, "|s", &name))
	{
		if (name)
			self->mID = InterfaceID(name ? Hash::Crc64(name, ::strlen(name)) : 0);
		else
			self->mID = InterfaceID(0);
		return 1;
	}
	return 0;
}

extern "C" Py_hash_t CPF_STDCALL Hash_InterfaceID(py::InterfaceID* self)
{
	return self->mID.GetID();
}

extern "C" PyObject* Compare_InterfaceID(PyObject *a, PyObject *b, int op)
{
	if (GOMInterfaceID_Check(b))
	{
		const GOM::InterfaceID& lhs = reinterpret_cast<py::InterfaceID*>(a)->mID;
		const GOM::InterfaceID& rhs = reinterpret_cast<py::InterfaceID*>(b)->mID;
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

extern PyGetSetDef GOMInterfaceID_getseters[];

extern PyTypeObject py::InterfaceID_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.InterfaceID",						/* tp_name */
	sizeof(py::InterfaceID),				/* tp_basicsize */
	0,										/* tp_itemsize */
	nullptr,								/* tp_dealloc */
	0,										/* tp_print */
	0,										/* tp_getattr */
	0,										/* tp_setattr */
	0,										/* tp_reserved */
	0,										/* tp_repr */
	0,										/* tp_as_number */
	0,										/* tp_as_sequence */
	0,										/* tp_as_mapping */
	(hashfunc)Hash_InterfaceID,				/* tp_hash  */
	0,										/* tp_call */
	0,										/* tp_str */
	0,										/* tp_getattro */
	0,										/* tp_setattro */
	0,										/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,						/* tp_flags */
	"Cpf objects",							/* tp_doc */
	nullptr,								/* tp_traverse */
	nullptr,								/* tp_clear */
	(richcmpfunc)Compare_InterfaceID,		/* tp_richcompare */
	0,										/* tp_weaklistoffset */
	nullptr,								/* tp_iter */
	nullptr,								/* tp_iternext */
	nullptr,								/* tp_methods */
	nullptr,								/* tp_members */
	GOMInterfaceID_getseters,				/* tp_getset */
	nullptr,								/* tp_base */
	nullptr,								/* tp_dict */
	nullptr,								/* tp_descr_get */
	nullptr,								/* tp_descr_set */
	0,										/* tp_dictoffset */
	(initproc)Init_InterfaceID,				/* tp_init */
	nullptr,								/* tp_alloc */
	nullptr,								/* tp_new */
	nullptr,								/* tp_free */
	nullptr,								/* tp_is_gc */
	nullptr,								/* tp_bases */
	nullptr,								/* tp_mro */
	nullptr,								/* tp_cache */
	nullptr,								/* tp_subclasses */
	nullptr,								/* tp_weaklist */
	nullptr,								/* tp_del */
	0,										/* tp_version_tag */
	nullptr									/* tp_finalize */
};


//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMInterfaceID_get_id(py::InterfaceID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMInterfaceID_set_id(py::InterfaceID* self, PyObject* value, void*)
{
	auto v = PyLong_AsUnsignedLongLong(value);
	self->mID = GOM::InterfaceID(v);
	return 0;
}

PyGetSetDef GOMInterfaceID_getseters[] =
{
	{ "id", (getter)GOMInterfaceID_get_id, (setter)GOMInterfaceID_set_id, nullptr, nullptr },
	{ NULL }
};

//////////////////////////////////////////////////////////////////////////
bool py::AddInterfaceIDType(PyObject* parent)
{
	py::InterfaceID_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&py::InterfaceID_type) < 0)
		return false;
	Py_INCREF(&py::InterfaceID_type);
	PyModule_AddObject(parent, "InterfaceID", reinterpret_cast<PyObject*>(&py::InterfaceID_type));

	return true;
}

//////////////////////////////////////////////////////////////////////////
#include "GOM/pyInterfaceID.hpp"
#include "GOM/pyResult.hpp"

using namespace Cpf;
using namespace GOM;


extern PyGetSetDef GOMInterfaceID_getseters[];

extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(py::InterfaceID* self);

extern "C" int CPF_STDCALL Init_GOMInterfaceID(py::InterfaceID* self, PyObject* args, PyObject* kwds)
{
	char* name = nullptr;
	if (!PyArg_ParseTuple(args, "|s", &name))
	{
		self->mID = GOM::InterfaceID(0);
		return -1;
	}
	self->mID = GOM::InterfaceID(name ? Hash::Crc64(name, ::strlen(name)) : 0);
	return 0;
}


static PyTypeObject GOMInterfaceID_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"gom.InterfaceID",						/* tp_name */
	sizeof(py::InterfaceID),				/* tp_basicsize */
	0,										/* tp_itemsize */
	(destructor)Dealloc_GOMInterfaceID,		/* tp_dealloc */
	0,										/* tp_print */
	0,										/* tp_getattr */
	0,										/* tp_setattr */
	0,										/* tp_reserved */
	0,										/* tp_repr */
	0,										/* tp_as_number */
	0,										/* tp_as_sequence */
	0,										/* tp_as_mapping */
	0,										/* tp_hash  */
	0,										/* tp_call */
	0,										/* tp_str */
	0,										/* tp_getattro */
	0,										/* tp_setattro */
	0,										/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,						/* tp_flags */
	"Cpf objects",							/* tp_doc */
	nullptr,								/* tp_traverse */
	nullptr,								/* tp_clear */
	nullptr,								/* tp_richcompare */
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
	(initproc)Init_GOMInterfaceID,			/* tp_init */
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
extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(py::InterfaceID *self)
{
	PyObject_Del(self);
}

#define GOMInterfaceID_Check(v)      (Py_TYPE(v) == &GOMInterfaceID_type)

extern "C" py::InterfaceID* CPF_STDCALL newGOMInterfaceID(PyObject *arg)
{
	(void)arg;
	py::InterfaceID *self;
	self = PyObject_New(py::InterfaceID, &GOMInterfaceID_type);
	if (self == nullptr)
		return nullptr;
	self->mID = GOM::InterfaceID(0);
	return self;
}

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
	GOMInterfaceID_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&GOMInterfaceID_type) < 0)
		return false;
	Py_INCREF(&GOMInterfaceID_type);
	PyModule_AddObject(parent, "InterfaceID", reinterpret_cast<PyObject*>(&GOMInterfaceID_type));

	return true;
}

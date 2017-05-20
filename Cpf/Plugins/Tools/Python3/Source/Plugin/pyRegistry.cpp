//////////////////////////////////////////////////////////////////////////
#include "Plugin/pyRegistry.hpp"
#include "GOM/pyResult.hpp"

using namespace Cpf;
using namespace Plugin;


static PyTypeObject PluginRegistry_type =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"plugin.Registry",			/* tp_name */
	sizeof(py::Registry),		/* tp_basicsize */
	0,							/* tp_itemsize */
	0,							/* tp_dealloc */
	0,							/* tp_print */
	0,							/* tp_getattr */
	0,							/* tp_setattr */
	0,							/* tp_reserved */
	0,							/* tp_repr */
	0,							/* tp_as_number */
	0,							/* tp_as_sequence */
	0,							/* tp_as_mapping */
	0,							/* tp_hash  */
	0,							/* tp_call */
	0,							/* tp_str */
	0,							/* tp_getattro */
	0,							/* tp_setattro */
	0,							/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,			/* tp_flags */
	"Cpf objects",				/* tp_doc */
	nullptr,					/* tp_traverse */
	nullptr,					/* tp_clear */
	nullptr,					/* tp_richcompare */
	0,							/* tp_weaklistoffset */
	nullptr,					/* tp_iter */
	nullptr,					/* tp_iternext */
	nullptr,					/* tp_methods */
	nullptr,					/* tp_members */
	nullptr,					/* tp_getset */
	nullptr,					/* tp_base */
};

#if 0
//////////////////////////////////////////////////////////////////////////
extern "C" void CPF_STDCALL Dealloc_GOMInterfaceID(PyObject_GOMResult *self)
{
	PyObject_Del(self);
}

#define GOMInterfaceID_Check(v)      (Py_TYPE(v) == &GOMInterfaceID_type)

extern "C" PyObject_GOMInterfaceID* CPF_STDCALL newGOMInterfaceID(PyObject *arg)
{
	(void)arg;
	PyObject_GOMInterfaceID *self;
	self = PyObject_New(PyObject_GOMInterfaceID, &GOMInterfaceID_type);
	if (self == nullptr)
		return nullptr;
	self->mID = GOM::InterfaceID(0);
	return self;
}

//////////////////////////////////////////////////////////////////////////
extern "C" PyObject* CPF_STDCALL GOMInterfaceID_get_id(PyObject_GOMInterfaceID* self, void*)
{
	return PyLong_FromUnsignedLongLong(self->mID.GetID());
}

extern "C" int CPF_STDCALL GOMInterfaceID_set_id(PyObject_GOMInterfaceID* self, PyObject* value, void*)
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
#endif

//////////////////////////////////////////////////////////////////////////
bool py::AddRegistryType(PyObject* parent)
{
	PluginRegistry_type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&PluginRegistry_type) < 0)
		return false;
	Py_INCREF(&PluginRegistry_type);
	PyModule_AddObject(parent, "Registry", reinterpret_cast<PyObject*>(&PluginRegistry_type));

	return true;
}

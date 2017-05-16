//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include <Python.h>
#include "rttr/registration.h"
#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;
using namespace Tools;

Python3::Python3(iUnknown*)
{}

Python3::~Python3()
{}

COM::Result CPF_STDCALL Python3::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iPython3*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

//////////////////////////////////////////////////////////////////////////
RTTR_REGISTRATION
{
	rttr::registration::class_<Plugin::iRegistry>("Cpf::Plugin::iRegistry")
		(
			rttr::metadata("ScriptExport", true)
		)
		.method("Load", &Plugin::iRegistry::Load)
		.method("Install", &Plugin::iRegistry::Install)
		.method("Remove", &Plugin::iRegistry::Remove)
		.method("Exists", &Plugin::iRegistry::Exists)
		.method("Create", &Plugin::iRegistry::Create)
		.method("ClassInstall", &Plugin::iRegistry::ClassInstall)
		.method("ClassRemove", &Plugin::iRegistry::ClassRemove)
		.method("GetClasses", &Plugin::iRegistry::GetClasses)
		.method("InstanceInstall", &Plugin::iRegistry::InstanceInstall)
		.method("InstanceRemove", &Plugin::iRegistry::InstanceRemove)
		.method("GetInstance", &Plugin::iRegistry::GetInstance)
	;
}


static PyModuleDef cpfModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf",
	"Core module integration with the Cpf frameworks.",
	-1,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

struct PythonRegistry
{
	PyObject_HEAD
		int64_t mTest;
};

static PyTypeObject cpfRegistryType =
{
	PyVarObject_HEAD_INIT(nullptr, 0)
	"cpf.Registry",            /* tp_name */
	sizeof(PythonRegistry),	   /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,        /* tp_flags */
	"Cpf objects",				/* tp_doc */
};

PyMODINIT_FUNC PyInit_cpf()
{
	cpfRegistryType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&cpfRegistryType) < 0)
		return nullptr;

	PyObject* m = PyModule_Create(&cpfModuleDef);
	if (m == nullptr)
		return m;

	Py_INCREF(&cpfRegistryType);
	PyModule_AddObject(m, "Registry", reinterpret_cast<PyObject*>(&cpfRegistryType));

	return m;
}


//////////////////////////////////////////////////////////////////////////

/* Use this file as a template to start implementing a module that
also declares object types. All occurrences of 'Xxo' should be changed
to something reasonable for your objects. After that, all other
occurrences of 'xx' should be changed to something reasonable for your
module. If your module is named foo your sourcefile should be named
foomodule.c.

You will probably want to delete all references to 'x_attr' and add
your own types of attributes instead.  Maybe you want to name your
local variables other than 'self'.  If your object type is needed in
other files, you'll have to create a file "foobarobject.h"; see
floatobject.h for an example. */

/* Xxo objects */
static PyObject *ErrorObject;

typedef struct {
	PyObject_HEAD
		PyObject            *x_attr;        /* Attributes dictionary */
} XxoObject;

void Xxo_dealloc(XxoObject *self);
int Xxo_setattr(XxoObject *self, const char *name, PyObject *v);
PyObject* Xxo_getattro(XxoObject *self, PyObject *name);
extern PyMethodDef Xxo_methods[2];

static PyTypeObject Xxo_Type = {
	/* The ob_type field must be initialized in the module init function
	* to be portable to Windows without using C++. */
	PyVarObject_HEAD_INIT(NULL, 0)
	"xxmodule.Xxo",             /*tp_name*/
	sizeof(XxoObject),          /*tp_basicsize*/
	0,                          /*tp_itemsize*/
								/* methods */
	(destructor)Xxo_dealloc,    /*tp_dealloc*/
	0,                          /*tp_print*/
	(getattrfunc)0,             /*tp_getattr*/
	(setattrfunc)Xxo_setattr,   /*tp_setattr*/
	0,                          /*tp_reserved*/
	0,                          /*tp_repr*/
	0,                          /*tp_as_number*/
	0,                          /*tp_as_sequence*/
	0,                          /*tp_as_mapping*/
	0,                          /*tp_hash*/
	0,                          /*tp_call*/
	0,                          /*tp_str*/
	(getattrofunc)Xxo_getattro, /*tp_getattro*/
	0,                          /*tp_setattro*/
	0,                          /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,         /*tp_flags*/
	0,                          /*tp_doc*/
	0,                          /*tp_traverse*/
	0,                          /*tp_clear*/
	0,                          /*tp_richcompare*/
	0,                          /*tp_weaklistoffset*/
	0,                          /*tp_iter*/
	0,                          /*tp_iternext*/
	Xxo_methods,                /*tp_methods*/
	0,                          /*tp_members*/
	0,                          /*tp_getset*/
	0,                          /*tp_base*/
	0,                          /*tp_dict*/
	0,                          /*tp_descr_get*/
	0,                          /*tp_descr_set*/
	0,                          /*tp_dictoffset*/
	0,                          /*tp_init*/
	0,                          /*tp_alloc*/
	0,                          /*tp_new*/
	0,                          /*tp_free*/
	0,                          /*tp_is_gc*/
};

#define XxoObject_Check(v)      (Py_TYPE(v) == &Xxo_Type)

static XxoObject *
newXxoObject(PyObject *arg)
{
	XxoObject *self;
	self = PyObject_New(XxoObject, &Xxo_Type);
	if (self == NULL)
		return NULL;
	self->x_attr = NULL;
	return self;
}

/* Xxo methods */

static void
Xxo_dealloc(XxoObject *self)
{
	Py_XDECREF(self->x_attr);
	PyObject_Del(self);
}

static PyObject *
Xxo_demo(XxoObject *self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, ":demo"))
		return NULL;
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef Xxo_methods[] = {
	{ "demo",            (PyCFunction)Xxo_demo,  METH_VARARGS,
	PyDoc_STR("demo() -> None") },
	{ NULL,              NULL }           /* sentinel */
};

static PyObject *
Xxo_getattro(XxoObject *self, PyObject *name)
{
	if (self->x_attr != NULL) {
		PyObject *v = PyDict_GetItem(self->x_attr, name);
		if (v != NULL) {
			Py_INCREF(v);
			return v;
		}
	}
	return PyObject_GenericGetAttr((PyObject *)self, name);
}

static int
Xxo_setattr(XxoObject *self, const char *name, PyObject *v)
{
	if (self->x_attr == NULL) {
		self->x_attr = PyDict_New();
		if (self->x_attr == NULL)
			return -1;
	}
	if (v == NULL) {
		int rv = PyDict_DelItemString(self->x_attr, name);
		if (rv < 0)
			PyErr_SetString(PyExc_AttributeError,
				"delete non-existing Xxo attribute");
		return rv;
	}
		
	return PyDict_SetItemString(self->x_attr, name, v);
}
/* --------------------------------------------------------------------- */

/* Function of two integers returning integer */

PyDoc_STRVAR(xx_foo_doc,
	"foo(i,j)\n\
\n\
Return the sum of i and j.");

static PyObject *
xx_foo(PyObject *self, PyObject *args)
{
	long i, j;
	long res;
	if (!PyArg_ParseTuple(args, "ll:foo", &i, &j))
		return NULL;
	res = i + j; /* XXX Do something here */
	return PyLong_FromLong(res);
}


/* Function of no arguments returning new Xxo object */

static PyObject *
xx_new(PyObject *self, PyObject *args)
{
	XxoObject *rv;

	if (!PyArg_ParseTuple(args, ":new"))
		return NULL;
	rv = newXxoObject(args);
	if (rv == NULL)
		return NULL;
	return (PyObject *)rv;
}

/* Example with subtle bug from extensions manual ("Thin Ice"). */

static PyObject *
xx_bug(PyObject *self, PyObject *args)
{
	PyObject *list, *item;

	if (!PyArg_ParseTuple(args, "O:bug", &list))
		return NULL;

	item = PyList_GetItem(list, 0);
	/* Py_INCREF(item); */
	PyList_SetItem(list, 1, PyLong_FromLong(0L));
	PyObject_Print(item, stdout, 0);
	printf("\n");
	/* Py_DECREF(item); */

	Py_INCREF(Py_None);
	return Py_None;
}

/* Test bad format character */

static PyObject *
xx_roj(PyObject *self, PyObject *args)
{
	PyObject *a;
	long b;
	if (!PyArg_ParseTuple(args, "O#:roj", &a, &b))
		return NULL;
	Py_INCREF(Py_None);
	return Py_None;
}


/* ---------- */

static PyTypeObject Str_Type = {
	/* The ob_type field must be initialized in the module init function
	* to be portable to Windows without using C++. */
	PyVarObject_HEAD_INIT(NULL, 0)
	"xxmodule.Str",             /*tp_name*/
	0,                          /*tp_basicsize*/
	0,                          /*tp_itemsize*/
								/* methods */
	0,                          /*tp_dealloc*/
	0,                          /*tp_print*/
	0,                          /*tp_getattr*/
	0,                          /*tp_setattr*/
	0,                          /*tp_reserved*/
	0,                          /*tp_repr*/
	0,                          /*tp_as_number*/
	0,                          /*tp_as_sequence*/
	0,                          /*tp_as_mapping*/
	0,                          /*tp_hash*/
	0,                          /*tp_call*/
	0,                          /*tp_str*/
	0,                          /*tp_getattro*/
	0,                          /*tp_setattro*/
	0,                          /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	0,                          /*tp_doc*/
	0,                          /*tp_traverse*/
	0,                          /*tp_clear*/
	0,                          /*tp_richcompare*/
	0,                          /*tp_weaklistoffset*/
	0,                          /*tp_iter*/
	0,                          /*tp_iternext*/
	0,                          /*tp_methods*/
	0,                          /*tp_members*/
	0,                          /*tp_getset*/
	0, /* see PyInit_xx */      /*tp_base*/
	0,                          /*tp_dict*/
	0,                          /*tp_descr_get*/
	0,                          /*tp_descr_set*/
	0,                          /*tp_dictoffset*/
	0,                          /*tp_init*/
	0,                          /*tp_alloc*/
	0,                          /*tp_new*/
	0,                          /*tp_free*/
	0,                          /*tp_is_gc*/
};

/* ---------- */

static PyObject *
null_richcompare(PyObject *self, PyObject *other, int op)
{
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyTypeObject Null_Type = {
	/* The ob_type field must be initialized in the module init function
	* to be portable to Windows without using C++. */
	PyVarObject_HEAD_INIT(NULL, 0)
	"xxmodule.Null",            /*tp_name*/
	0,                          /*tp_basicsize*/
	0,                          /*tp_itemsize*/
								/* methods */
	0,                          /*tp_dealloc*/
	0,                          /*tp_print*/
	0,                          /*tp_getattr*/
	0,                          /*tp_setattr*/
	0,                          /*tp_reserved*/
	0,                          /*tp_repr*/
	0,                          /*tp_as_number*/
	0,                          /*tp_as_sequence*/
	0,                          /*tp_as_mapping*/
	0,                          /*tp_hash*/
	0,                          /*tp_call*/
	0,                          /*tp_str*/
	0,                          /*tp_getattro*/
	0,                          /*tp_setattro*/
	0,                          /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	0,                          /*tp_doc*/
	0,                          /*tp_traverse*/
	0,                          /*tp_clear*/
	null_richcompare,           /*tp_richcompare*/
	0,                          /*tp_weaklistoffset*/
	0,                          /*tp_iter*/
	0,                          /*tp_iternext*/
	0,                          /*tp_methods*/
	0,                          /*tp_members*/
	0,                          /*tp_getset*/
	0, /* see PyInit_xx */      /*tp_base*/
	0,                          /*tp_dict*/
	0,                          /*tp_descr_get*/
	0,                          /*tp_descr_set*/
	0,                          /*tp_dictoffset*/
	0,                          /*tp_init*/
	0,                          /*tp_alloc*/
	0, /* see PyInit_xx */      /*tp_new*/
	0,                          /*tp_free*/
	0,                          /*tp_is_gc*/
};


/* ---------- */


/* List of functions defined in the module */

static PyMethodDef xx_methods[] = {
	{ "roj",             xx_roj,         METH_VARARGS,
	PyDoc_STR("roj(a,b) -> None") },
	{ "foo",             xx_foo,         METH_VARARGS,
	xx_foo_doc },
	{ "new",             xx_new,         METH_VARARGS,
	PyDoc_STR("new() -> new Xx object") },
	{ "bug",             xx_bug,         METH_VARARGS,
	PyDoc_STR("bug(o) -> None") },
	{ NULL,              NULL }           /* sentinel */
};

PyDoc_STRVAR(module_doc,
	"This is a template module just for instruction.");


static int
xx_exec(PyObject *m)
{
	/* Due to cross platform compiler issues the slots must be filled
	* here. It's required for portability to Windows without requiring
	* C++. */
	Null_Type.tp_base = &PyBaseObject_Type;
	Null_Type.tp_new = PyType_GenericNew;
	Str_Type.tp_base = &PyUnicode_Type;

	/* Finalize the type object including setting type of the new type
	* object; doing it here is required for portability, too. */
	if (PyType_Ready(&Xxo_Type) < 0)
		goto fail;

	/* Add some symbolic constants to the module */
	if (ErrorObject == NULL) {
		ErrorObject = PyErr_NewException("xx.error", NULL, NULL);
		if (ErrorObject == NULL)
			goto fail;
	}
	Py_INCREF(ErrorObject);
	PyModule_AddObject(m, "error", ErrorObject);

	/* Add Str */
	if (PyType_Ready(&Str_Type) < 0)
		goto fail;
	PyModule_AddObject(m, "Str", (PyObject *)&Str_Type);

	/* Add Null */
	if (PyType_Ready(&Null_Type) < 0)
		goto fail;
	PyModule_AddObject(m, "Null", (PyObject *)&Null_Type);
	return 0;
fail:
	Py_XDECREF(m);
	return -1;
}

static struct PyModuleDef_Slot xx_slots[] = {
	{ Py_mod_exec, xx_exec },
	{ 0, NULL },
};

static struct PyModuleDef xxmodule = {
	PyModuleDef_HEAD_INIT,
	"xx",
	module_doc,
	0,
	xx_methods,
	xx_slots,
	NULL,
	NULL,
	NULL
};

/* Export function for the module (*must* be called PyInit_xx) */

PyMODINIT_FUNC
PyInit_xx(void)
{
	return PyModuleDef_Init(&xxmodule);
}
//////////////////////////////////////////////////////////////////////////

/*
 * I think that the goal is going to be centralized around rttr.
 * Describe the API's to rttr and then pass those into the script
 * component which will then break it down into appropriate bindings.
 * This will allow multiple script languages at the cost of speed,
 * but since this is intended as only being a tool only solution
 * it doesn't matter much.
 */

COM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
{
	// TODO: Redirect this properly to an asynchronous data sink
	// so the streams can be parsed, placed in different windows,
	// and most importantly, to the CPF_LOG system.
#ifdef CPF_DEBUG
#	if CPF_TARGET_WINDOWS
	AllocConsole();
	SetConsoleTitle("Python3");
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#	endif
#endif

	//////////////////////////////////////////////////////////////////////////
	// Create a Cpf module.
	PyImport_AppendInittab("cpf", &PyInit_cpf);
	PyImport_AppendInittab("xo", &PyInit_xx);
	Py_Initialize();


	//////////////////////////////////////////////////////////////////////////
	// List out the registered iRegistry.
	CPF_LOG(Python3, Info) << "Begin rttr: *******************************************";
	for (const auto& type : rttr::type::get_types())
	{
		if (type.is_class())
		{
			if (type.get_metadata("Test").is_valid())
			{
				CPF_LOG(Python3, Info) << type.get_name();
				for (const auto& method : type.get_methods())
				{
					CPF_LOG(Python3, Info) << " :" << method.get_name() << " Args(" << method.get_parameter_infos().size() << ")";
				}
			}
		}
	}
	CPF_LOG(Python3, Info) << "End rttr:   *******************************************";
	//////////////////////////////////////////////////////////////////////////

	WString wpath;
	for (int i = 0; basePath[i] != 0; ++i)
		wpath.push_back(wchar_t(basePath[i]));
	PySys_SetPath(wpath.c_str());

	PyObject* pName = PyUnicode_DecodeFSDefault("TestPython");
	PyObject* pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != nullptr)
	{
		PyObject* pFunc = PyObject_GetAttrString(pModule, "multiply");
		if (pFunc && PyCallable_Check(pFunc))
		{
			PyObject* pArgs = PyTuple_New(2);
			PyObject* pValue = PyLong_FromLong(5);
			PyTuple_SetItem(pArgs, 0, pValue);
			pValue = PyLong_FromLong(7);
			PyTuple_SetItem(pArgs, 1, pValue);

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				CPF_LOG(Python3, Info) << "Python test result is 5*7 = " << PyLong_AsLong(pValue);
				Py_DECREF(pValue);
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	return COM::kOK;
}

COM::Result CPF_STDCALL Python3::Shutdown()
{
	Py_FinalizeEx();
	return COM::kOK;
}

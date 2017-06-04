//////////////////////////////////////////////////////////////////////////
#include "GOM/pyModule.hpp"
#include "GOM/pyMethods.hpp"
#include "GOM/pyResult.hpp"
#include "GOM/pyClassID.hpp"
#include "GOM/pyInterfaceID.hpp"

using namespace Cpf;
using namespace GOM;

static PyModuleDef CpfGomModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"cpf.gom",
	"GOM module integration.",
	-1,
	py::CpfGOM_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

bool py::AddModule(PyObject* parent)
{
	PyObject* module = PyModule_Create(&CpfGomModuleDef);
	if (module == nullptr)
	{
		return false;
	}

	AddResultType(module);
	AddClassIDType(module);
	AddInterfaceIDType(module);

	PyModule_AddObject(parent, "gom", module);
	return true;
}

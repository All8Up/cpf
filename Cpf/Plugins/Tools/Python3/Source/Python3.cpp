//////////////////////////////////////////////////////////////////////////
#include "Python3.hpp"
#include "Logging/Logging.hpp"
#include <Python.h>
#include "pybind11/pybind11.h"

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
struct Pet {
	Pet(const std::string &name) : name(name) { }
	void setName(const std::string &name_) { name = name_; }
	const std::string &getName() const { return name; }

	std::string name;
};

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
	py::module m("example", "pybind11 example plugin");

	py::class_<Pet>(m, "Pet")
		.def(py::init<const std::string &>())
		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName);

	return m.ptr();
}

COM::Result CPF_STDCALL Python3::Initialize(const char* basePath)
{
	Py_Initialize();
	auto example = pybind11_init();

	WString wpath;
	for (int i = 0; basePath[i] != 0; ++i)
		wpath.push_back(wchar_t(basePath[i]));
	PySys_SetPath(wpath.c_str());

	auto module = pybind11::module::import("TestPython");
	auto func = module.attr("multiply");
	auto result = func(2, 5);
	auto rval = result.cast<long>();

	Py_DECREF(example);
	return COM::kOK;
}

COM::Result CPF_STDCALL Python3::Shutdown()
{
	Py_FinalizeEx();
	return COM::kOK;
}

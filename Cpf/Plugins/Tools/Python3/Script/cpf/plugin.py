import cpfcore
import ctypes
from cpf import gom

class IID_CID(ctypes.Structure):
	_fields_ = [
		('iid', ctypes.c_uint64),
		('cid', ctypes.c_uint64)
	]

class iRegistry(gom.iBase):
	_methods_ =	[
		('Load', gom.Method(ctypes.c_uint32, ctypes.c_char_p)),
		('Unload', gom.Method(ctypes.c_uint32, ctypes.c_char_p)),
		('Install', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p)),
		('Remove', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('GetClassInstance', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p)),
		('Exists', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('Create', gom.Method(ctypes.c_uint32, ctypes.c_void_p, ctypes.c_uint64, ctypes.c_uint64, ctypes.c_void_p)),
		('ClassInstall', gom.Method(ctypes.c_uint32, ctypes.c_int32, ctypes.POINTER(IID_CID))),
		('ClassRemove', gom.Method(ctypes.c_uint32, ctypes.c_int32, ctypes.POINTER(IID_CID))),
		('GetClasses', gom.Method(ctypes.c_uint32, ctypes.POINTER(ctypes.c_int32), ctypes.POINTER(IID_CID))),
		('InstanceInstall', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p)),
		('InstanceRemove', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('GetInstance', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p))
	]

class iClassInstance(gom.iBase):
	_methods_ = [
		('CreateInstance', gom.Method(ctypes.c_uint32, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p))
	]


localModule = ctypes.CDLL('plugins/Python3.cfp')
cpf_create_registry = localModule.CpfCreateRegistry
cpf_create_registry.argtypes = [ctypes.c_void_p]

def create_registry():
	registry = iRegistry()
	cpf_create_registry(ctypes.byref(registry))
	return registry

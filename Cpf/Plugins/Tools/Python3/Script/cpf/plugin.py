import cpfcore
import ctypes
from cpf import gom

class iRegistry(gom.iBase):
	_methods_ =	[
		('Load', gom.Method(ctypes.c_uint32, ctypes.c_char_p)),
		('CanUnload', gom.Method(ctypes.c_uint32, ctypes.c_char_p)),
		('Unload', gom.Method(ctypes.c_uint32, ctypes.c_char_p)),
		('Install', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p)),
		('Remove', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('Exists', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('Create', gom.Method(ctypes.c_uint32, ctypes.c_void_p, ctypes.c_uint64, ctypes.c_uint64, ctypes.c_void_p)),
		('ClassInstall', gom.Method(ctypes.c_uint32, ctypes.c_int32, ctypes.c_void_p)),
		('ClassRemove', gom.Method(ctypes.c_uint32)),
		('GetClasses', gom.Method(ctypes.c_uint32)),
		('InstanceInstall', gom.Method(ctypes.c_uint32)),
		('InstanceRemove', gom.Method(ctypes.c_uint32, ctypes.c_uint64)),
		('GetInstance', gom.Method(ctypes.c_uint32))
	]

'''
GOM::Result Load(const char* const library) = 0;
GOM::Result CanUnload(const char* const library) = 0;
GOM::Result Unload(const char* const library) = 0;
GOM::Result Install(GOM::ClassID cid, iClassInstance* clsInst) = 0;
GOM::Result Remove(GOM::ClassID cid) = 0;
GOM::Result Exists(GOM::ClassID cid) = 0;
GOM::Result Create(iBase* outer, GOM::ClassID cid, GOM::InterfaceID iid, void** result) = 0;
GOM::Result ClassInstall(int32_t count, const IID_CID* pairs) = 0;
GOM::Result ClassRemove(int32_t count, const IID_CID* pairs) = 0;
GOM::Result GetClasses(GOM::InterfaceID id, int32_t* count, GOM::ClassID* cid) = 0;
GOM::Result InstanceInstall(GOM::InterfaceID id, iBase* instance) = 0;
GOM::Result InstanceRemove(GOM::InterfaceID id) = 0;
GOM::Result GetInstance(GOM::InterfaceID id, iBase** outIface) = 0;
'''

localModule = ctypes.CDLL('plugins/Python3.cfp')
cpf_create_registry = localModule.CpfCreateRegistry
cpf_create_registry.argtypes = [ctypes.c_void_p]

def create_registry():
	registry = iRegistry()
	cpf_create_registry(ctypes.byref(registry))
	return registry

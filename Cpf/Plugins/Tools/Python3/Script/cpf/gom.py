import ctypes
import cpf
from builtins import object

class Method(object):
    ''' GOM method. '''
    def __init__(self, restype, *args):
        self.restype = restype
        self.argtypes = args

    def get_field(self):
        return ctypes.WINFUNCTYPE(self.restype, *self.argtypes)

class MethodInstance(object):
    ''' Binds a GOM interface method. '''
    def __init__(self, name, i, method):
        self.name = name
        self.i = i
        self.method = method

    def __get__(self, obj, tp):
        if obj is not None:
            def _call(*args):
                return self.method.get_field()(self.i, self.name)(obj, *args)
            return _call
        raise AttributeError()

class Base(ctypes.Structure):
    ''' Interface pointers are just a vtable pointer, member data is hidden from the caller. '''
    _fields_ = [('pVtable', ctypes.c_void_p),]

class MetaBase(type(ctypes.POINTER(Base))):
    ''' This wraps the interface pointer to indirect through the vtable. '''
    def __new__(cls, name, bases, dct):
        methods = []
        for base in bases[::-1]:
            methods.extend(base.__dict__.get('_methods_', ()))
        methods.extend(dct.get('_methods_', ()))

        for i, (n, method) in enumerate(methods):
            dct[n] = MethodInstance(n, i, method)

        dct['_type_'] = Base
        return super(MetaBase, cls).__new__(cls, name, bases, dct)

Interface = MetaBase(str('Interface'), (ctypes.POINTER(Base),), {
    '__doc__': 'GOM Interface pointer.',
    })

Result = ctypes.c_uint32

class iUnknown(Interface):
    _methods_ =	[
        ('AddRef', Method(ctypes.c_int32)),
        ('Release', Method(ctypes.c_int32)),
        ('QueryInterface', Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p))
    ]

def make_result(err, ss, v):
	result = 0
	result = result | (err << 31) | (ss << 16) | v
	return result

OK = make_result(0, cpf.crc15('Core'), cpf.crc16('OK'))

def success(result):
	return (result & 0x80000000) == 0

def failure(result):
	return (result & 0x80000000) != 0

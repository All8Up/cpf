import ctypes
from builtins import object

class Method(object):
	''' Base wrapper for interface methods. '''
	def __init__(self, rtype, *args):
		self.rtype = rtype
		self.args = args

	def get(self):
		return ctypes.WINFUNCTYPE(self.rtype, *self.args)

class MethodInstance(object):
	''' Binding for an interface method. '''
	def __init__(self, name, vtblidx, method):
		self.name = name
		self.vtblidx = vtblidx
		self.method = method

	def __get__(self, obj, tp):
		if obj is not None:
			def _call(*args):
				return self.method.get()(self.vtblidx, self.name)(obj, *args)
			return _call
		raise AttributeError()

class Base(ctypes.Structure):
	''' Interface pointers are just a vtable pointer, member data is hidden from the caller. '''
	_fields_ = [('pVtable', ctypes.c_void_p)]

class MetaBase(type(ctypes.POINTER(Base))):
	''' This wraps the interface pointer to indirect through the vtable. '''
	def __new__(cls, name, bases, dct):
		meths = []
		for base in bases[::-1]:
			meths.extend(base.__dict__.get('_methods_', ()))
		meths.extend(dct.get('_methods_', ()))

		for i, (n, method) in enumerate(meths):
			dct[n] = MethodInstance(n, i, method)
		dct['_type_'] = Base
		return super(MetaBase, cls).__new__(cls, name, bases, dct)

Interface = MetaBase(str('Interface'), (ctypes.POINTER(Base),), {
	'__doc__': 'GOM Interface pointer.',
	})

import gc
import unittest
import cpf
import ctypes
from cpf import plugin
from cpf import gom
from builtins import object

class GOMMethod(object):
	''' Base wrapper for interface methods. '''
	def __init__(self, rtype, *args):
		self.rtype = rtype
		self.args = args

	def get(self):
		return ctypes.WINFUNCTYPE(self.rtype, *self.args)

class GOMMethodInstance(object):
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

class GOMBase(ctypes.Structure):
	''' Interface pointers are just a vtable pointer, member data is hidden from the caller. '''
	_fields_ = [('pVtable', ctypes.c_void_p)]

class GOMMetaBase(type(ctypes.POINTER(GOMBase))):
	''' This wraps the interface pointer to indirect through the vtable. '''
	def __new__(cls, name, bases, dct):
		methods = []
		for base in bases[::-1]:
			methods.extend(base.__dict__.get('_methods_', ()))
		methods.extend(dct.get('_methods_', ()))

		for i, (n, method) in enumerate(methods):
			print (i, n)
			dct[n] = GOMMethodInstance(n, i, method)
		dct['_type_'] = GOMBase
		return super(GOMMetaBase, cls).__new__(cls, name, bases, dct)

Interface = GOMMetaBase(str('Interface'), (ctypes.POINTER(GOMBase),), {
	'__doc__': 'GOM Interface pointer.',
	})

class iBase(Interface):
	_methods_ =	[
		('AddRef', GOMMethod(ctypes.c_int32)),
		('Release', GOMMethod(ctypes.c_int32)),
		('Cast', GOMMethod(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p))
	]

class iTest(iBase):
	_methods_ = [
		('Tester', GOMMethod(ctypes.c_int32, ctypes.c_int64))
	]




class Tests(unittest.TestCase):
	def setUp(self):
		self.registry = plugin.create_registry()
		self.assertTrue(self.registry.load('plugins/TestingPlugin.cfp'))
		self.testInstance = iTest()
		self.registry.create(gom.ClassID('Testing::iTest'), gom.InterfaceID('Testing::iTest'), ctypes.byref(self.testInstance))

	def tearDown(self):
		self.assertEqual(self.testInstance.Release(), 0)
		self.assertTrue(self.registry.unload('plugins/TestingPlugin.cfp'))

	def testCIDExists(self):
		self.assertTrue(self.registry.exists(gom.ClassID('Testing::iTest')))

	def testCTypeWrapper(self):
		for i in range(0, 10):
			result = self.testInstance.Tester(i)
			self.assertEqual(result, i)

def run_tests():
	print('------ Testing plugin.Registry -----')
	print("cpf.plugin.Registry contents:")
	print(dir(plugin.Registry))
	print('--------------------------------')

	print('------ Complete ------')
	registry = plugin.create_registry()

	# Test loading the test plugin.
	if not registry.load('plugins/TestingPlugin.cfp'):
		print("Failure: registry.load('plugins/TestingPlugin.cfp')")

	# Test that the test plugin can be unloaded at this time.
	if not registry.can_unload('plugins/TestingPlugin.cfp'):
		print("Failure: registry.can_unload('plugins/TestingPlugin.cfp')")

	# Test that the test plugin has registered the expected class id.
	if not registry.exists(gom.ClassID('Testing::iTest')):
		print("Failure: registry.exists did not find the expected class instance.")

	# Create an instance of the test class.
	try:
		test = registry.create(gom.ClassID('Testing::iTest'), gom.InterfaceID('Testing::iTest'))
	except RuntimeError:
		print("Failure: registry.create failed to create test plugin.")

	# Test that the interface id has a class instance associated with it.
	classes = registry.get_classes(gom.InterfaceID('Testing::iTest'))
	if classes == None or len(classes) != 1:
		print("Failure: classes not as expected")
	# Test that the class ID is as expected.
	if classes[0] != gom.ClassID('Testing::iTest'):
		print("Failure: returned class id not as expected")
	classes = None

	# Install the test plugin instance as the implementation of the interface id.
	registry.instance_install(gom.InterfaceID('Testing::iTest'), test)
	# Retrieve the implementation back from the registry and make sure it is what was installed.
	test3 = registry.get_instance(gom.InterfaceID('Testing::iTest'))
	# Remove the instance from the registry.
	registry.instance_remove(gom.InterfaceID('Testing::iTest'))

	# Release the test instance and force a garbage collection.
	# NOTE: If this is not done, a crash will happen since unloading the plugin will invalidate the vtables.
	test = None
	test2 = None
	test3 = None
	gc.collect()

	# Re-validate that we can unload the plugin at this time.

	# Unload the test plugin.
	if not registry.unload('plugins/TestingPlugin.cfp'):
		print("Failure: registry.unload('plugins/TestingPlugin.cfp')")
	print (plugin.Registry.iid)
	print (registry.iid)

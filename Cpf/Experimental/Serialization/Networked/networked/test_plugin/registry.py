import gc
import unittest
import cpf
from cpf import plugin
from cpf import gom

class Tests(unittest.TestCase):
	def setUp(self):
		self.registry = plugin.create_registry()
		self.assertTrue(self.registry.load('plugins/TestingPlugin.cfp'))

	def tearDown(self):
		self.assertTrue(self.registry.unload('plugins/TestingPlugin.cfp'))

	def testCIDExists(self):
		self.assertTrue(self.registry.exists(gom.ClassID('Testing::iTest')))


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

	# Validate that we got the correct instance created.
	test2 = gom.cast(test, gom.InterfaceID('Testing::iTest'))
	if test != test2:
		print("Failure: gom.cast failure")

	# Call the generic add_ref and release just to test the instance.
	gom.add_ref(test)
	gom.release(test)

	# Validate that the plugin says it can not be unloaded at this time.
	# --- TODO

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

import gc
import cpf
from cpf import plugin
from cpf import gom

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
	gom.add_ref(test)
	gom.release(test)

	# Validate that we got the correct instance created.
	# Call the test function on the instance.
	# Validate that the plugin says it can not be unloaded at this time.
	# Test that the interface id has a class instance associated with it.
	# Test that the class ID is as expected.
	# Install the test plugin instance as the implementation of the interface id.
	# Retrieve the implementation back from the registry and make sure it is what was installed.
	# Remove the instance from the registry.
	# Release the test instance and force a garbage collection.
	test = None
	gc.collect()

	# Re-validate that we can unload the plugin at this time.

	# Unload the test plugin.
	if not registry.unload('plugins/TestingPlugin.cfp'):
		print("Failure: registry.unload('plugins/TestingPlugin.cfp')")
	print (plugin.Registry.iid)
	print (registry.iid)

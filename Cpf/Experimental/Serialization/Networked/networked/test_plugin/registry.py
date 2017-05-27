import cpf
from cpf import plugin

def run_tests():
	print('------ Testing plugin.Registry -----')
	print("cpf.plugin.Registry contents:")
	print(dir(plugin.Registry))
	print('--------------------------------')

	print('------ Complete ------')
	registry = plugin.create_registry()
	if not registry.load('plugins/Scene.cfp'):
		print("Failure: registry.load('plugins/Scene.cfp')")
	if not registry.can_unload('plugins/Scene.cfp'):
		print("Failure: registry.can_unload('plugins/Scene.cfp')")
	if not registry.unload('plugins/Scene.cfp'):
		print("Failure: registry.unload('plugins/Scene.cfp')")
	print (plugin.Registry.iid)
	print (registry.iid)

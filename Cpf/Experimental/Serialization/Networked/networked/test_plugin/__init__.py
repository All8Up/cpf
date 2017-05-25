from cpf import plugin
from test_plugin import registry

def run_tests():
	print('--------------------------------')
	print ('cpf.plugin contents:')
	print (dir(plugin))
	print('--------------------------------')
	registry.run_tests()

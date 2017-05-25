from cpf import gom
from test_gom import result
from test_gom import classid
from test_gom import interfaceid
from test_gom import methods
from test_gom import base

# I would like to use unittest but it doesn't seem to want to import in my environment.
def run_tests():
	print('--------------------------------')
	print ('cpf.gom contents:')
	print (dir(gom))
	print('--------------------------------')
	methods.run_tests()
	classid.run_tests()
	interfaceid.run_tests()
	result.run_tests()
	base.run_tests()

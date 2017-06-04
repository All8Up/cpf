import sys
import io
import unittest

class IntegrationTest(unittest.TestCase):
	def	test_paths(self):
		print('--------------------------------')
		print('System path:')
		print(sys.path)
		print('--------------------------------')
		

verbosity = 2
runner = unittest.TextTestRunner(verbosity=verbosity)
suite = unittest.defaultTestLoader.loadTestsFromTestCase(IntegrationTest)
runner.run(suite)

print('--------------------------------')
print('--------------------------------')

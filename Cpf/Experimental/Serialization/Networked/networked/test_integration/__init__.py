import sys
import io
import unittest
import test_gom
import test_plugin

class IntegrationTest(unittest.TestCase):
	def	test_paths(self):
		print('System path:')
		print(sys.path)

verbosity = 2
runner = unittest.TextTestRunner(verbosity=verbosity)
runner.run(test_gom.GetSuite())
runner.run(test_plugin.GetSuite())

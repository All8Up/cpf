import unittest
from test_plugin import registry

def GetSuite():
	suite = unittest.TestSuite()
	suite.addTests(unittest.defaultTestLoader.loadTestsFromTestCase(registry.Tests))
	return suite

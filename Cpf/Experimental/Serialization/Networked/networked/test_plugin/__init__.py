import unittest
from cpf import plugin
from test_plugin import registry

def GetSuite():
	suite = unittest.TestSuite()
	tests = unittest.defaultTestLoader.loadTestsFromTestCase(registry.Tests)
	suite.addTests(tests)
	return suite

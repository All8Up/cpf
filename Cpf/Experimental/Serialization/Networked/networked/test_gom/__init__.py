import unittest
from cpf import gom
from test_gom import methods
from test_gom import result
from test_gom import classid
from test_gom import interfaceid

def GetSuite():
	suite = unittest.TestSuite()
	suite.addTests(unittest.defaultTestLoader.loadTestsFromTestCase(methods.Tests))
	suite.addTests(unittest.defaultTestLoader.loadTestsFromTestCase(result.Tests))
	suite.addTests(unittest.defaultTestLoader.loadTestsFromTestCase(classid.Tests))
	suite.addTests(unittest.defaultTestLoader.loadTestsFromTestCase(interfaceid.Tests))
	return suite

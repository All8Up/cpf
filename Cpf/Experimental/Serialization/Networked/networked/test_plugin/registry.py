import ctypes
import unittest
import cpfcore
from cpf import gom
from cpf import plugin

iTestCID = cpfcore.crc64('Testing::iTest')

class iTest(gom.iBase):
	iid = cpfcore.crc64('Testing::iTest')
	_methods_ =	[
		('Tester', gom.Method(ctypes.c_int32, ctypes.c_int64))
	]


class Tests(unittest.TestCase):
	def setUp(self):
		self.pluginId = cpfcore.crc64('Testing::iTest')
		self.registry = plugin.create_registry()
		self.registry.Load("plugins/TestingPlugin.cfp".encode('utf-8'))
		self.plugin = iTest()
		self.registry.Create(0, iTestCID, iTest.iid, ctypes.byref(self.plugin))

	def tearDown(self):
		self.registry.Unload("plugins/TestingPlugin.cfp".encode('utf-8'))
		self.assertEqual(self.registry.Release(), 0)

	def testAddRelease(self):
		self.assertEqual(self.registry.AddRef(), 2)
		self.assertEqual(self.registry.Release(), 1)

	def testExists(self):
		self.assertEqual(self.registry.Exists(self.pluginId), gom.OK)

	def testPluginCall(self):
		self.assertEqual(self.plugin.Tester(67), 67)

import unittest
import ctypes
import cpf
from cpf import gom
from cpf import plugin

iTestCID = cpf.crc64('Testing::iTest')
class iTest(gom.iBase):
	iid = cpf.crc64('Testing::iTest')
	_methods_ =	[
		('Tester', gom.Method(ctypes.c_int32, ctypes.c_int64))
	]


class Tests(unittest.TestCase):
	def setUp(self):
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
		self.assertEqual(self.registry.Exists(iTestCID), gom.OK)

	def testPluginCall(self):
		self.assertEqual(self.plugin.Tester(67), 67)

	def testRemove(self):
		# Go get the class instance first.
		tempClassInstance = plugin.iClassInstance()
		self.assertTrue(gom.success(self.registry.GetClassInstance(iTestCID, ctypes.byref(tempClassInstance))))

		# Test removing the class instance and then double check it was actually removed.
		self.assertTrue(gom.success(self.registry.Exists(iTestCID)))
		self.assertTrue(gom.success(self.registry.Remove(iTestCID)))
		self.assertTrue(gom.failure(self.registry.Exists(iTestCID)))

		# Put the class instance back into the factory.  The factory steals
		# the reference given us by GetClassInstance, so we don't release.
		self.assertTrue(gom.success(self.registry.Install(iTestCID, tempClassInstance)))

import ctypes
import unittest
from cpf import gom
from cpf import plugin

class Tests(unittest.TestCase):
	def setUp(self):
		self.registry = plugin.create_registry()
		self.registry.Load("plugins/TestingPlugin.cfp".encode('utf-8'))

	def tearDown(self):
		self.registry.Unload("plugins/TestingPlugin.cfp".encode('utf-8'))
		self.assertEqual(self.registry.Release(), 0)

	def test_AddRelease(self):
		self.assertEqual(self.registry.AddRef(), 2)
		self.assertEqual(self.registry.Release(), 1)


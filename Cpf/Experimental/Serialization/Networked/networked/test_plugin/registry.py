import ctypes
import unittest
from cpf import gom
from cpf import plugin

class Tests(unittest.TestCase):
	def setUp(self):
		self.registry = plugin.create_registry()
		print (self.registry.AddRef())
		print (self.registry.Release())
		self.registry.Load("plugins/TestingPlugin.cfp".encode('utf-8'))

	def tearDown(self):
		self.registry.Release()
		pluginName = ctypes.c_char_p("plugins/TestingPlugin.cfp".encode('utf-8'))
		print (pluginName)
		self.registry.Unload(pluginName)
		pass

	def	test_paths(self):
		print('System path:')

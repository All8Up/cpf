import cpf
import ctypes
import unittest
from cpf import gom

class iBase(gom.Interface):
	_methods_ =	[
		('AddRef', gom.Method(ctypes.c_int32)),
		('Release', gom.Method(ctypes.c_int32)),
		('Cast', gom.Method(ctypes.c_uint32, ctypes.c_uint64, ctypes.c_void_p))
	]

class iTest(iBase):
	_methods_ = [
		('Tester', gom.Method(ctypes.c_int32, ctypes.c_int64))
	]


class Tests(unittest.TestCase):
	def	test_paths(self):
		print('System path:')

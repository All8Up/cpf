import _cpf
import ctypes

def createRegistry():
	capsule = _cpf.createRegistry()
	ctypes.pythonapi.PyCapsule_GetPointer.restype = ctypes.c_void_p
	ctypes.pythonapi.PyCapsule_GetPointer.argtypes = [ctypes.py_object, ctypes.c_char_p]
	return ctypes.pythonapi.PyCapsule_GetPointer(capsule, None)

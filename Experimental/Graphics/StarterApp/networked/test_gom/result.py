import unittest
import cpf
from cpf import gom

class Tests(unittest.TestCase):
	def setUp(self):
		self.successResult = gom.Result(error=0, subsystem='Core', value='Not an error')
		self.failureResult = gom.Result(error=1, subsystem='Core', value='An error')

	def tearDown(self):
		self.successResult = None
		self.failureResult = None

	def testSuccess_Error(self):
		self.assertEqual(self.successResult.error, 0, 'Error value should be zero')

	def testSuccess_SubSystem(self):
		self.assertEqual(self.successResult.subsystem, cpf.crc16('Core'), 'Invalid subsystem string crc')

	def testSuccess_Value(self):
		self.assertEqual(self.successResult.value, cpf.crc15('Not an error'), 'Invalid error string crc')

	def testHelper_SuccessPass(self):
		self.assertTrue(gom.succeeded(self.successResult), 'Success result should pass')

	def testHelper_FailedFail(self):
		self.assertFalse(gom.failed(self.successResult), 'Success should not fail')

	def testFailure_Error(self):
		self.assertEqual(self.failureResult.error, 1, 'Error value should be one')

	def testFailure_SubSystem(self):
		self.assertEqual(self.failureResult.subsystem, cpf.crc16('Core'), 'Invalid subsystem string crc')

	def testFailure_Value(self):
		self.assertEqual(self.failureResult.value, cpf.crc15('An error'), 'Invalid error string crc')

	def testHelper_FailurePass(self):
		self.assertTrue(gom.failed(self.failureResult), 'Failure result should pass')

	def testHelper_FailureFail(self):
		self.assertFalse(gom.succeeded(self.failureResult), 'Failure should fail')

import cpf
from cpf import gom

def run_tests():
	print('------ Testing gom.Result ------')
	print("cpf.gom.Result contents:")
	print(dir(gom.Result))
	print('--------------------------------')

	successResult = gom.Result(error=0, subsystem='Core', value='Not an error')
	failResult = gom.Result(error=1, subsystem='Core', value='An error')

	# Test access of success code.
	if successResult.error != 0:
		print ("Failure: successResult.error != 0")
	if successResult.subsystem != cpf.crc16('Core'):
		print ("Failure: successResult.subsystem != cpf.crc16('Core')")
	if successResult.value != cpf.crc15('Not an error'):
		print ("Failure: successResult.value != cpf.crc15('Not an error')")
	# Test helper checks.
	if not gom.succeeded(successResult):
		print ("Failure: gom.succeeded(successResult)")
	if gom.failed(successResult):
		print ("Failure: gom.failed(successResult)")

	# Test access of failure code.
	if failResult.error != 1:
		print ("Failure: failResult.error != 1")
	if failResult.subsystem != cpf.crc16('Core'):
		print ("Failure: failResult.subsystem != cpf.crc16('Core')")
	if failResult.value != cpf.crc15('An error'):
		print ("Failure: failResult.value != cpf.crc15('An error')")
	# Test helper checks.
	if gom.succeeded(failResult):
		print ("Failure: gom.succeeded(failResult)")
	if not gom.failed(failResult):
		print ("Failure: gom.failed(failResult)")

	print('------ Complete ------')

import cpf
from cpf import gom
from cpf import plugin

print (dir(cpf))
print ('-------------------------------')
print (dir(gom))
print ('-------------------------------')
print (dir(plugin))
print ('-------------------------------')
successResult = gom.Result(error=0, subsystem='Core', value='Not and error')
print ("successResult.error: ", successResult.error)
print ("successResult.subsystem: ", successResult.subsystem)
print ("successResult.value: ", successResult.value)
if gom.succeeded(successResult):
	print ("succcessResult succeeded")
else:
	print ("successResult failed")
if gom.failed(successResult):
	print ("succcessResult failed")
else:
	print ("successResult succeeded")
failResult = gom.Result(error=1, subsystem='Core', value='An error')
print ("failResult.error: ", failResult.error)
print ("failResult.subsystem: ", failResult.subsystem)
print ("failResult.value: ", failResult.value)
if gom.succeeded(failResult):
	print ("failResult succeeded")
else:
	print ("failResult failed")
if gom.failed(failResult):
	print ("failResult failed")
else:
	print ("failResult succeeded")

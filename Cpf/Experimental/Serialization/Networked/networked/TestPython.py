import cpf
from cpf import gom

print (dir(cpf))
print ('-------------------------------')
print (dir(gom))
print ('-------------------------------')
testResult = gom.Result(error=0, subsystem='Core', value='Not and error')
print ("testResult.error: ", testResult.error)
print ("testResult.subsystem: ", testResult.subsystem)
print ("testResult.value: ", testResult.value)

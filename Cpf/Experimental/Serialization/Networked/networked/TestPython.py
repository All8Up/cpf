import cpf

y = cpf.Result()
z = y.is_error()
print ("is_error: ", z)
print ("error: ", y.error)
print ("subsystem: ", y.subsystem)
print ("value: ", y.value)
print ("success: ", cpf.succeeded(y))
print ("failed: ", cpf.failed(y))
print (dir(y))
print ("-------------------------------")
print(dir(cpf))
print ("-------------------------------")

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b

    return c

'''
def test_registry():
	registry = Registry()
	result = registry.exists()
	print ("Exists: ", result)
'''

import cpf
import xx

print ("-------------------------------")
print (dir(xx))
print ("-------------------------------")
y = xx.Result
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

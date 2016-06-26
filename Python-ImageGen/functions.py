import math
import random

def sigmoid(x):
    return x / (math.sqrt(x**2 + 1))

def trigTemplate(trig_function):
    '''Pre: x is a float in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    def template(x, y):
        return trig_function((mapToHalfCircle(x))+1.0)/2.0
    return template

def sine(x, y):
    return trigTemplate(math.sin)(x, y)

def cosine(x, y):
    return trigTemplate(math.cos)(x, y)

def gaussian(x, y):
    '''Pre: x and y are floats in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    return math.e ** -(mapToHalfCircle(x)**2 + mapToHalfCircle(y)**2)

def average(x,y):
    '''Pre: x and y are floats in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    return (x+y)/2.0

def product(x,y):
    '''Pre: x and y are floats in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    return x*y

def absoluteval(x,_):
    '''Pre: x is a float in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    return abs((x*2.0)-1.0)

def power(x,y):
    '''Pre: x and y are floats in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    return x**y

def modulo(x,y):
    '''Pre: x and y are floats in the interval -math.pi/2.0 to math.pi/2.0
    Post: returns a value in the range 0 to 1'''
    if y == 0: return x
    else: return x%y

def mapToHalfCircle(x):
    '''Pre: x is in the range 0 to 1
    Post: returns a value in the range -math.pi/2.0 to math.pi/2.0'''
    return (x*math.pi) - (math.pi/2)

def compose(functions):
    def result(x, y):

        for function in functions[:-1]:
            x = function(x, y)
            y = function(y, x)

        return (functions[-1])(x, y)

    return result

function_array = [sine, cosine, gaussian, average, product, absoluteval, power, modulo]

functions = {}
for function in function_array:
    functions[function.__name__] = function

custom = compose([random.choice(function_array) for x in range(10)])

def test_function(x, y):
    x = sigmoid(x)
    y = sigmoid(y)

    r = custom(x, y)
    g = custom(y, x)
    b = custom(x**y, y**x)
    return [r, g, b, 1]

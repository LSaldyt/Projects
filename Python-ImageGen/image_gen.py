from PIL       import Image
from functions import test_function

img_size = 256

def getImage(function):
    data = []
    '''Takes a function with two inputs that returns an array of 3 integers,
    and a returns an array of pixels'''

    for y in range(img_size):
        for x in range(img_size):
                outputs = function(x/img_size,
                                   y/img_size)
                mapToPixel = lambda i : int(outputs[i] * 255)
                pixels = mapToPixel(0), mapToPixel(1), mapToPixel(2), mapToPixel(3)
                data.append(pixels)

    return data

data = getImage(test_function)

img = Image.new('RGBA', (img_size, img_size))
img.putdata(data)
img.save("image.png")

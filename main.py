f = open('test.ply', 'r')

print f.read()

points = []

stop = False
length = 0

while not stop:
    a = f.readline().find('element vertex')

    if a is not None:
        length = float()
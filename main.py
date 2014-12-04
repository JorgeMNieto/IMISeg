import numpy as np
f = open('test.ply', 'r')

points = []

length = 0
footer_length = 0
header_length = 0;

iterations_limit = 20
iterations = 0;
while True:
    iterations += 1
    a = f.readline()
    if 'element vertex' in a:
        b = a.replace('element vertex', '')
        length = int(b.strip())

    if 'element face' in a:
        b = a.replace('element face', '')
        footer_length = int(b.strip())

    if iterations == iterations_limit:
        break

    if 'end_header' in a:
        header_length = iterations
        points = np.genfromtxt('test.ply', skip_header=header_length, skip_footer=footer_length)
        print points
        break

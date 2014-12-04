import sys
import numpy as np

if len(sys.argv) < 2:
    sys.exit('Usage: main.py <file_path>')

file_path = str(sys.argv[1])
f = open(file_path, 'r')

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
        points = np.genfromtxt(file_path, skip_header=header_length, skip_footer=footer_length)
        print(points)
        break

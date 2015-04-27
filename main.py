import sys
import numpy as np

def take(elements, number, offset):
    """Returns a new array containing a _number_ of _elements_ from a given _offset_.

    The element at _offset_ is included.
    """
    assert offset + number <= len(elements), "Insufficent elements to take."

    return [ elements[i] for i in range(offset, offset + number) ]

def surface_normal(three_points):
    assert len(three_points) == 3, "Expected three points, %r given." % len(three_points)

    v1 = three_points[0]
    v2 = three_points[1]
    v3 = three_points[2]
    return np.cross(v3 - v1, v3 - v2)

def compute_normals(points):
    index = 0;
    normals = []
    while index < len(points):
        normal = surface_normal(take(points, 3, index))

        for i in range(3):
            normals.append(normal)

        index = index + 3
    return normals

def main(args):
    if len(args) < 1:
        sys.exit('Usage: main.py <file_path>')

    file_path = str(args[0])
    f = open(file_path, 'r')

    length = 0
    footer_length = 0
    header_length = 0;

    iterations_limit = 20
    iterations = 0;

    in_header = True
    while in_header and iterations < iterations_limit:
        iterations += 1
        a = f.readline()
        if 'element vertex' in a:
            b = a.replace('element vertex', '')
            length = int(b.strip())

        if 'element face' in a:
            b = a.replace('element face', '')
            footer_length = int(b.strip())

        if 'end_header' in a:
            header_length = iterations
            in_header = False

    f.close()

    points = np.genfromtxt(file_path, skip_header=header_length, skip_footer=footer_length)

    print(compute_normals(points))

if __name__ == '__main__':
    main(sys.argv[1:])

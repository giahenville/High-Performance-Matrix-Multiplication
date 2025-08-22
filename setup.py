"""
Generates NxN random numbers that are spaced separated and writes them to a shared file
"""

import sys
import random

def setup(N):
    with open('MatA.txt', 'w') as file:
        for i in range(0, N):
            for j in range(0, N):
                file.write(str(random.randint(1, 10)) + " ")
            file.write("\n")
    with open('MatB.txt', 'w') as file:
        for i in range(0, N):
            for j in range(0, N):
                file.write(str(random.randint(1, 10)) + " ")
            file.write("\n")

     
if __name__ == "__main__":
    if len(sys.argv) < 1:
        print("expected: python setup.py [N]\nN: size of square matrix")
    else:
        setup(int(sys.argv[1]))

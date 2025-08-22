"""
Generates NxN random numbers that are spaced separated and writes them to a shared file
"""

import sys
import random

def setup(N):
    with open('../data/MatA.txt', 'w') as file:
        for i in range(0, N):
            for j in range(0, N):
                file.write(str(random.randint(1, 10)) + " ")
            file.write("\n")
    with open('../data/MatB.txt', 'w') as file:
        for i in range(0, N):
            for j in range(0, N):
                file.write(str(random.randint(1, 10)) + " ")
            file.write("\n")

     
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: python3 {sys.argv[0]} <N>\n<N>  Size of the square matrix to generate\nExample: python3 {sys.argv[0]} 128")
    else:
        setup(int(sys.argv[1]))

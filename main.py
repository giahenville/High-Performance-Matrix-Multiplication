import torch
import time

# Arguments MatA and MatB are PyTorch tensors!
def GPUAcceleratedMMUL(MatA, MatB):
    MatC = torch.matmul(MatA, MatB) 
    return MatC

def NaiveMMUL(MatA, MatB):
    # Here, we are MatA and MatB are equal, square-matrices
    N = MatA.shape[0]
    MatC = torch.zeros(size=(N, N), device=MatA.device)

    for row in range(N):
        for col in range(N):
            for element in range(N):
                MatC[row][col] += MatA[row][element] * MatB[element][col]

    return MatC

def FileToTensor(filename):
    Mat = []
    with open(filename, "r") as file:
        for line in file:
            line = line.rstrip().split(" ")
            for i in range(len(line)):
                line[i] = int(line[i])
            Mat.append(line)
    return torch.tensor(Mat)

def main():
    # read in MatA.txt and MatB.txt and store them as a PyTorch tensor
    device = torch.device("mps" if torch.backends.mps.is_available() else "cpu")
    MatA = FileToTensor("MatA.txt")
    MatB = FileToTensor("MatB.txt")
    MatA = MatA.to(device)
    MatB = MatB.to(device)

    # conversion to microseconds
    micro = 1e6

    # testing naive python implementation
    start = time.time()
    NaiveMMUL(MatA, MatB)
    end = time.time()
    naiveTime = (end - start) * micro
    print(f"Python: NaiveMMUL\ntime to execute: {naiveTime:.4f}")

    # testing pytorch matmul implementation
    _ = torch.matmul(MatA, MatB) # warmup (important for gpu benchmarking)
    torch.mps.synchronize()

    start = time.time()
    GPUAcceleratedMMUL(MatA, MatB)
    torch.mps.synchronize()
    end = time.time()
    gpuAccelTime = (end - start) * micro
    print(f"Python: GPUAcceleratedMMUL\ntime to execute: {gpuAccelTime:.4f}")


if __name__ == "__main__":
    main()

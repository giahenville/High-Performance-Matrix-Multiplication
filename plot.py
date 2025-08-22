import pandas as pd
import matplotlib.pyplot as plt

# Load data
data = pd.read_csv("benchmark_results.csv")

# Plot
plt.figure(figsize=(10,6))
plt.plot(data["N"], data["C++_Naive_us"], marker="o", label="C++ Naive")
plt.plot(data["N"], data["Python_Naive_us"], marker="o", label="Python Naive")
plt.plot(data["N"], data["Python_GPU_us"], marker="o", label="Python GPU")

plt.xscale("log", base=2)
plt.yscale("log")
plt.xlabel("Matrix Size N (NxN)")
plt.ylabel("Execution Time (µs)")
plt.title("Matrix Multiplication Performance Benchmark")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.tight_layout()

plt.show()

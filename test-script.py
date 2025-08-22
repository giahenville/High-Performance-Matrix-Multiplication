"""

Automates MMUL calculations (C++ naive, Python naive, and Python GPUAccel) for 
graphing purposes

"""

import subprocess
import re
import csv
import statistics

# matrix sizes to test
SIZES = [1, 2, 4, 8, 16, 32, 64, 128]

# number of repetitions per size
REPEATS = 5

# regex to capture runtime (microseconds or µs)
time_pattern = re.compile(r"time to execute:\s*([\d.]+)")

results = []

for N in SIZES:
    print(f"\nRunning size {N}x{N}")
    # setup input matrices
    subprocess.run(["python3", "setup.py", str(N)], check=True)

    cpp_times = []
    py_naive_times = []
    py_gpu_times = []

    for i in range(REPEATS):
        # run C++ naive
        cpp_out = subprocess.run(["./main"], capture_output=True, text=True, check=True)
        cpp_match = time_pattern.search(cpp_out.stdout)
        if cpp_match:
            cpp_times.append(float(cpp_match.group(1)))

        # run Python naive + GPU
        py_out = subprocess.run(["python3", "main.py"], capture_output=True, text=True, check=True)

        # naive (first line match)
        py_matches = time_pattern.findall(py_out.stdout)
        if len(py_matches) == 2:
            py_naive_times.append(float(py_matches[0]))
            py_gpu_times.append(float(py_matches[1]))

    # compute averages
    cpp_avg = statistics.mean(cpp_times) if cpp_times else None
    py_naive_avg = statistics.mean(py_naive_times) if py_naive_times else None
    py_gpu_avg = statistics.mean(py_gpu_times) if py_gpu_times else None

    results.append({
        "N": N,
        "C++_Naive_us": cpp_avg,
        "Python_Naive_us": py_naive_avg,
        "Python_GPU_us": py_gpu_avg
    })

# save to CSV
with open("benchmark_results.csv", "w", newline="") as csvfile:
    fieldnames = ["N", "C++_Naive_us", "Python_Naive_us", "Python_GPU_us"]
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(results)

print("completed benchmark")

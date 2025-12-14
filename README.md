# High-Frequency Poker Engine (HFT-C++)

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg) ![License](https://img.shields.io/badge/license-MIT-green.svg) ![Latency](https://img.shields.io/badge/latency-%3C1ms-orange)

A low-latency Texas Hold'em solver engine engineered for **high-frequency equity calculation** and **Nash Equilibrium approximation**.

## 🚀 Key Technical Features

* **O(1) Hand Evaluation:** Implemented "Cactus Kev" Prime-Product algorithm with perfect hashing for constant-time lookups.
* **Bitmask Optimization:** State representation using 64-bit integers to minimize cache misses and memory overhead.
* **Vectorized MCCFR:** Multi-threaded Monte Carlo Counterfactual Regret Minimization for solving imperfect information games.
* **Foreign Function Interface (FFI):** Zero-copy `ctypes` bridge allowing Python to drive the C++ engine without serialization overhead.

## 🛠️ Architecture
The system follows a hybrid architecture common in HFT firms:
1.  **Core Engine (C++17):** Handles memory management, RNG, and simulation loops.
2.  **Control Layer (Python):** Manages strategy logic, data visualization, and game flow.

## ⚡ Benchmarks
* **Throughput:** ~30 Million hand evaluations/sec (Single Thread)
* **Latency:** < 1.5ms per decision node on standard hardware.

## 📦 Build & Run

### Prerequisites
* G++ (C++17 support)
* Python 3.8+

### Compilation
```bash
# 1. Generate the Lookup Table (Pre-computation)
g++ -std=c++17 -O3 generator.cpp -o generator
./generator

# 2. Build the Shared Library (Engine)
# For Linux/Mac:
g++ -std=c++17 -O3 -shared -fPIC wrapper.cpp poker.cpp evaluator.cpp monte_carlo.cpp -o libpoker.so
# For Windows:
g++ -std=c++17 -O3 -shared wrapper.cpp poker.cpp evaluator.cpp monte_carlo.cpp -o libpoker.dll

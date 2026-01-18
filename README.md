# High-Frequency Poker Engine (HFT-C++)

![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg) ![License](https://img.shields.io/badge/license-MIT-green.svg) ![Latency](https://img.shields.io/badge/latency-%3C1.5ms-orange)

A low-latency Texas Hold'em equity calculator engineered for **high-throughput Monte Carlo simulation** and real-time decision making.

## 🚀 Key Technical Features

* **O(1) Hand Evaluation:** Implemented "Cactus Kev" Prime-Product algorithm with perfect hashing (`evaluator.cpp`) for constant-time lookups.
* **Bitmask Optimization:** State representation using 32-bit integers to minimize cache misses and memory overhead.
* **Parallelized Monte Carlo:** Multi-threaded simulation engine using `std::async` and `std::future` (`monte_carlo.cpp`) to batch simulations across available CPU cores.
* **Foreign Function Interface (FFI):** Zero-copy `extern "C"` bridge (`wrapper.cpp`) allowing Python to drive the C++ engine without serialization overhead.

## 🛠️ Architecture
The system follows a hybrid architecture optimized for performance:
1.  **Core Engine (C++):** Handles memory management, bitwise logic, and the simulation loop.
2.  **Control Layer (Python):** Manages strategy logic, game flow, and data visualization via `ctypes`.

## ⚡ Benchmarks
* **Throughput:** ~30 Million hand evaluations/sec (Single Thread)
* **Latency:** < 20ms per 50k simulation batch on standard hardware.

## 📦 Build & Run

### Prerequisites
* G++ (C++20 support recommended)
* Python 3.8+

### Compilation
```bash
# 1. Generate the Lookup Table (Pre-computation)
g++ -std=c++20 -O3 generator.cpp -o generator
./generator

# 2. Build the Shared Library (Engine)
# For Linux/Mac:
g++ -std=c++20 -O3 -shared -fPIC wrapper.cpp poker.cpp evaluator.cpp monte_carlo.cpp -o libpoker.dylib
# Note: Output name 'libpoker.dylib' matches bot.py configuration. Use .so for Linux.

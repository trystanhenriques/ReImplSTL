# ReImplSTL

A personal learning project where I reimplement common C++ STL data structures from scratch.

**This is not meant to be a production-ready library.** The sole purpose is to deepen my understanding of data structures and how the STL works under the hood, by building them myself in C++.

## Building

### Prerequisites

- CMake 3.20 or later
- A C++17-capable compiler:
  - **macOS**: Xcode Command Line Tools (`xcode-select --install`) or a Homebrew-installed Clang/GCC
  - **Windows**: Visual Studio 2019/2022 (with the "Desktop development with C++" workload) or MinGW-w64

### macOS – Command Line

```bash
cmake -S . -B build
cmake --build build
# Optional: run the smoke test via CTest
ctest --test-dir build --output-on-failure
```

### macOS – CLion

1. Open the repository folder in CLion (`File > Open`).  
   CLion detects `CMakeLists.txt` automatically and configures the project.
2. Select the **ReImplSTL** run configuration and press **Run** or **Debug**.

### macOS – Xcode

```bash
cmake -S . -B build-xcode -G Xcode
open build-xcode/ReImplSTL.xcodeproj
```

### Windows – Visual Studio

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Or open the repository folder directly in **Visual Studio 2019/2022** (`File > Open > Folder`);
Visual Studio's built-in CMake support will configure the project automatically.


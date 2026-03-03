cmake_minimum_required(VERSION 3.20)
project(ReImplSTL CXX)

# ── C++ standard ────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Header-only library target ───────────────────────────────────────────────
add_library(reimplstl_headers INTERFACE)
target_include_directories(reimplstl_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# ── Compiler warnings (cross-platform) ──────────────────────────────────────
if(MSVC)
    target_compile_options(reimplstl_headers INTERFACE /W4 /WX)
else()
    target_compile_options(reimplstl_headers INTERFACE -Wall -Wextra -Wpedantic)
endif()

# ── Main executable ──────────────────────────────────────────────────────────
add_executable(ReImplSTL ReImplSTL.cpp)
target_link_libraries(ReImplSTL PRIVATE reimplstl_headers)

# ── CTest integration ────────────────────────────────────────────────────────
enable_testing()
add_test(NAME smoke_test COMMAND ReImplSTL)

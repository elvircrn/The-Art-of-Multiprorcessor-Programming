cmake_minimum_required(VERSION 3.12)
project(ch16)

set(CMAKE_CXX_STANDARD 17)

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_executable(ch16_addition examples/matrix_addition/addition_pool.cpp multiprocessing/ThreadPool.h multiprocessing/BDequeue.h examples/common.h util/atomic128.h util/bitutil.h)
#add_executable(ch16_bdequeue multiprocessing/ThreadPool.h multiprocessing/BDequeue.h examples/common.h util/atomic128.h util/bitutil.h)

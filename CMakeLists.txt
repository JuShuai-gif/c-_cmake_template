cmake_minimum_required(VERSION 3.16)
project(c_cmake_template)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 设置生成可执行文件的位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 包含glog日志
include(cmake/FindGlog.cmake)

# 添加源文件
aux_source_directory(./src DIR_DATA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 设置glog库
set(link_lib ${GLOG_LIBRARIES})

# 添加多线程库
IF (!WIN32)
    set(link_lib ${link_lib} pthread)
ENDIF ()

# 构造链接库
add_library(c_cmake_template SHARED ${DIR_DATA})

# 附加链接库
target_link_libraries(c_cmake_template ${link_lib})

# 添加头文件
target_include_directories(c_cmake_template PUBLIC ${glog_INCLUDE_DIR})
target_include_directories(c_cmake_template PUBLIC ${GTest_INCLUDE_DIR})

# 本项目的开发者请使用set(DEVELOPMENT ON)或者在cmake中添加-DDEVELOPMENT=ON将选项打开
# 单元测试
option(BUILD_TESTS "Should we build tests?" ON)

if (BUILD_TESTS)
    MESSAGE(STATUS "BUILD TEST PROJECT")
    enable_testing()
    add_subdirectory(test)
endif()

# 是否构建 example
option(BUILD_EXAMPLE "BUILD THE DEMO PROJECT" ON)

# 是否构建demo
if (BUILD_EXAMPLE)
    MESSAGE(STATUS "BUILD EXAMPLE PROJECT")
    add_subdirectory(example)
endif ()

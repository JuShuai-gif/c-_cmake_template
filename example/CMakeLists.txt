cmake_minimum_required(VERSION 3.10)
project(example)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 添加源码目录
add_executable(example main.cpp)

# 添加库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 链接库
target_link_libraries(example c_cmake_template)

# 如果你的库是动态库，可以使用以下命令添加库搜索路径
# target_link_libraries(MyProject ${PROJECT_SOURCE_DIR}/lib/libyourlibrary.so)



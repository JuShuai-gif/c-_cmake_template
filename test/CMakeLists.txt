find_package(GTest REQUIRED)
include(../cmake/FindGlog.cmake)
find_package(LAPACK REQUIRED)

# 添加测试源文件
aux_source_directory(../test/data DIR_DATA_RUNTIME)
aux_source_directory(../test/parse DIR_PARSE_RUNTIME)

set(link_lib ${GLOG_LIBRARIES} GTest::gtest)

if (!WIN32)
    set(link_lib "${link_lib} pthread")
endif ()

find_package(GTest REQUIRED)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

# 添加库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 设置链接库
set(link_lib ${GLOG_LIBRARIES} GTest::gtest c_cmake_template)

macro(cxx_test pretty_name bin_name sources libs)

    add_executable(${bin_name} ${sources} test_main.cpp)

    target_link_libraries(${bin_name} ${libs} ${link_lib} ${GTEST_BOTH_LIBRARIES})
    target_include_directories(${bin_name} PUBLIC ${glog_INCLUDE_DIR})
    target_include_directories(${bin_name} PUBLIC ${GTest_INCLUDE_DIR})
    add_test(${pretty_name} ${bin_name})
    add_dependencies(check ${bin_name})
endmacro()

cxx_test("TEST::test_data" test_data ${DIR_DATA_RUNTIME} "-pthread")

cxx_test("TEST::test_parse" test_parse ${DIR_PARSE_RUNTIME} "-pthread")
cmake_minimum_required(VERSION 3.16)
project(GateServer CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Boost路径
set(BOOST_ROOT "/usr/include/boost")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# 查找Boost，如果没有Boost库，CMake会报错
find_package(Boost REQUIRED)

# 设置jsoncpp路径
set(JSONCPP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../jsoncpp")
set(JSONCPP_INCLUDE_DIR "${JSONCPP_ROOT}/include")
set(JSONCPP_SOURCES
    ${JSONCPP_ROOT}/src/lib_json/json_reader.cpp
    ${JSONCPP_ROOT}/src/lib_json/json_writer.cpp
    ${JSONCPP_ROOT}/src/lib_json/json_value.cpp
)

# 设置Gateserver源文件
set(GATESERVER_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/httpconnection.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/logicsystem.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/mainserver.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)

# 包含目录
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIR})

# 源文件
set(SOURCES
    ${GATESERVER_SOURCES}
    ${JSONCPP_SOURCES}
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接库
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
)
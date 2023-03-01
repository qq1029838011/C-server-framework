#cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#工程名称
PROJECT(mordor)

#cmake生成的详细信息
SET(CMAKE_VERBOSE_MAKEFILE ON)
#设置预编译指令
SET(CMAKE_CXX_FLAGS "%ENV{CXXFLAGS} -rdynamic -03 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

#设置日志库源文件路径
SET(LIB_SRC server/log.cc)

#生成动态库
ADD_LIBRARY(server SHARED ${LIB_SRC})

#生成可执行程序
ADD_EXECUTABLE(test tests/test.cc)
#指定目标依赖
ADD_DEPENDENCIES(test server)
#将目标文件链接到第三方库
TARGET_LINK_LIBRARIES(test server)

#设置可执行程序的输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设置库输出路径
SET(LIB_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

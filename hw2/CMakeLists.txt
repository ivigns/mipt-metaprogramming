cmake_minimum_required(VERSION 3.15)
project(factory_generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(factory_generator main.cpp TypeList.h Util.h FactoryGetter.h GenHierarchy.h)
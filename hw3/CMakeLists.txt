cmake_minimum_required(VERSION 3.15)
project(hw3)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw3 main.cpp TypeList.h Functor.h VisitorAcceptor.h VisitDispatcher.h Utils.h)
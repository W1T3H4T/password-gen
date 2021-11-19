cmake_minimum_required(VERSION 2.8)

project(password-gen)

add_executable(password-gen main.cpp)

install(TARGETS password-gen DESTINATION /usr/local/bin)

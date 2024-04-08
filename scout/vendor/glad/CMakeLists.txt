cmake_minimum_required(VERSION 3.10)

project(glad)

add_library(glad STATIC glad/khrplatform.h glad/glad.c glad/glad.h)

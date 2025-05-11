cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER 
	Server/server.cpp
	Include/httplib.h
	Methods/mainMethod.cpp 
	)

set(CLIENT 
	Client/client.cpp
	Include/httplib.h
	Tests/tests.cpp
	)

#include_directories (Include, Methods, Tests)

add_executable(server ${SERVER})
add_executable(client ${CLIENT})

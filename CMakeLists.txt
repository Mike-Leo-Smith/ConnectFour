cmake_minimum_required(VERSION 3.7)
project(ConnectFour)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

set(SOURCE_FILES
		main.cpp
		Game/game.cpp
		Game/game.h
		MCTS/node.cpp
		MCTS/node.h
		MCTS/allocator.cpp
		MCTS/allocator.h
		MCTS/tree.cpp
		MCTS/tree.h
		Clock/clock.cpp
		Clock/clock.h)
add_executable(ConnectFour ${SOURCE_FILES})
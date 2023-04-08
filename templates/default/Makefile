.PHONY: build

build: main

main: main.cpp
	g++ -std=c++11 -Wall -Wextra -Wshadow -fsanitize=address -fsanitize=undefined -DLOCAL -D_GLIBCXX_DEBUG -g main.cpp -o main

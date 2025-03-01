all: main

main: main.cpp dbg.h
	g++ -std=c++17 -Wall -Wextra main.cpp -o main

debug: main.cpp dbg.h
	g++ -std=c++17 -Wall -Wextra -DLOCAL -g main.cpp -o main

clean:
	rm -rf main.dSYM main
.PHONY: clean

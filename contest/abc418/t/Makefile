CXX := g++

DEBUG := true

CXXFLAGS := -std=c++17 \
		-Wall \
		-Wextra \
		-Wno-deprecated \

DEBUG_CXXFLAGS := -DLOCAL -g

ifeq ($(DEBUG),true)
CXXFLAGS += $(DEBUG_CXXFLAGS)
endif

all: main

main: main.cpp dbg.h
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) -o main

clean:
	rm -rf main.dSYM main compile_commands.json
.PHONY: clean

cleanall:
	rm -rf main.dSYM main compile_commands.json *.in *.ans *.out in out ans
.PHONY: cleanall

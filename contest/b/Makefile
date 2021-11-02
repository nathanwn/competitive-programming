GNU_GCC_PATH := "/opt/homebrew/Cellar/gcc/14.2.0_1"

DEBUG := true

CXXFLAGS := -std=c++17 \
		-Wall \
		-Wextra \
		-Wno-deprecated \
		-I$(GNU_GCC_PATH)/include/c++/14 \
		-I$(GNU_GCC_PATH)/include/c++/14/aarch64-apple-darwin24 \
		-stdlib=libstdc++ \
		-nostdinc++

LDFLAGS := -L/opt/homebrew/opt/gcc/lib/gcc/14 -Wl,-rpath,/opt/homebrew/opt/gcc/lib/gcc/14

DEBUG_CXXFLAGS := \
		-fsanitize=address \
		# Disable ubsan on MacOS ARM as it is unstable and often results in weird
		# false positives in my experience
		-fno-sanitize=undefined \
		-fno-sanitize-recover=all \
		-D_GLIBCXX_DEBUG \
		-D_GLIBCXX_DEBUG_PEDANTIC \
		-DLOCAL -g


ifeq ($(DEBUG),true)
CXXFLAGS += $(DEBUG_CXXFLAGS)
endif

all: main

main: main.cpp dbg.h
	MallocNanoZone=0 g++ $(CXXFLAGS) main.cpp $(LDFLAGS) -o main

clean:
	rm -rf main.dSYM main
.PHONY: clean

CXX := g++
DEBUG := true

CLEAN_TARGETS :=

MAIN_TARGET := main
BRUTE_TARGET := brute
CLEAN_TARGETS += $(MAIN_TARGET)
CLEAN_TARGETS += $(BRUTE_TARGET)

EXEC := ./$(MAIN_TARGET)

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -Wshadow -Wformat=2 \
			-Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-qual -Wcast-align \
			-Wno-unused-result -Wno-sign-conversion

DEBUG_CXXFLAGS := -fsanitize=address \
				  -fsanitize=undefined \
				  -fsanitize=float-divide-by-zero \
				  -fsanitize=float-cast-overflow \
				  -fno-sanitize-recover=all \
				  -fstack-protector-all \
				  -D_FORTIFY_SOURCE=2 \
				  -D_GLIBCXX_DEBUG \
				  -D_GLIBCXX_DEBUG_PEDANTIC \
				  -DLOCAL \
				  -g

ifeq ($(DEBUG),true)
CXXFLAGS += $(DEBUG_CXXFLAGS)
$(info DEBUG enabled)
endif

# === Build targets
# For regular testing
test: $(MAIN_TARGET)
.PHONY: test

# For stress testing
stress: $(MAIN_TARGET) $(BRUTE_TARGET)
.PHONY: stress

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# === Run targets
# Input files
IN_FILES := $(sort $(basename $(wildcard *.in)))
ANS_FILES := $(sort $(basename $(wildcard *.ans)))

# Run an compare
test: $(patsubst %,_test_%_,$(ANS_FILES))
	$(info === $< ===)
.PHONY: test

_test_%_: %.out %.ans
# Consider adding -B or -w if necessary
	diff -B $*.out $*.ans
.PHONY: _test_%_

# Run only
run: $(patsubst %,%.out,$(IN_FILES))
	$(info === $< ===)
.PHONY: run

%.out: $(TARGET) %.in
	\time $(EXEC) < $*.in > $*.out
.PRECIOUS: %.out

clean:
	rm -rf $(CLEAN_TARGETS) *.out
.PHONY: clean

veryclean: clean
	rm -rf .cache
.PHONY: veryclean

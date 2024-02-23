# Makefile to run test cases with Valgrind for memory leak checks

# Define a shell to be used by make
SHELL=/bin/bash

# Define test case numbers
TEST_CASES := $(shell seq 1 10)

# Phony target to handle all tests including Valgrind checks
.PHONY: all valgrind
all: $(TEST_CASES)
valgrind: $(addprefix valgrind_,$(TEST_CASES))

build: MyQuicksort_t984h395.hpp
	g++ -std=c++11 MainTest.cpp -o Lab1

# Rule to run each test case
$(TEST_CASES): build
	@echo "Running Test Case $@"
	- /usr/bin/gtime -v -o Logs/log_$@.txt ./Lab1 Inputs/input_$@.txt > result_$@.txt
	- python3 GradingScript.py result_$@.txt Outputs/output_$@.txt Logs/log_$@.txt Logs/log_$@.txt 2659.851

# Rule to run Valgrind for each test case
valgrind_%: build
	@echo "Running Valgrind for Test Case $*"
	- valgrind --leak-check=full --log-file=Logs/valgrind_log_$*.txt ./Lab1 Inputs/input_$*.txt > /dev/null
	- python3 GradingScript.py /dev/null Outputs/output_$*.txt Logs/valgrind_log_$*.txt Logs/valgrind_log_$*.txt 2659.851

# Clean up generated files
.PHONY: clean
clean:
	rm -f result_*.txt Logs/log_*.txt Logs/valgrind_log_*.txt Lab1

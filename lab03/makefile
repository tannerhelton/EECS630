# Define test case numbers
TEST_CASES := $(shell seq 1 10)

# Phony target to handle all tests
.PHONY: all
all: $(TEST_CASES)

build: MyClosestPairOfPoints_t984h395.h
	g++ -std=c++11 MainTest.cpp -o Lab

# Rule to run each test case
$(TEST_CASES): clean build
	@echo "Running Test Case $@"
	- /usr/bin/time -v -o result_log_$@.txt ./Lab Inputs/input_$@.txt > result_$@.txt
	- python3 GradingScript.py result_$@.txt Outputs/output_$@.txt result_log_$@.txt Logs/log_$@.txt 2659.851

# Clean up generated files
.PHONY: clean
clean:
	rm -f result_*.txt Lab result_log_*.txt test_result

# Define test case numbers
TEST_CASES := $(shell seq 1 10)

# Phony target to handle all tests
.PHONY: all
all: $(TEST_CASES)

build: MyEditDistance_t984h395.hpp
	g++ -std=c++11 MainTest.cpp -o Lab

# Rule to run each test case
$(TEST_CASES): clean build
	@echo "Running Test Case $@"
	- /usr/bin/time -v -o result_log_$@.txt ./Lab Inputs/input_$@.txt > result_$@.txt
	- python3 GradingScript.py result_$@.txt Outputs/output_$@.txt result_log_$@.txt Logs/log_$@.txt 2955.158

print: result_1.txt
	@echo "Test Case 1 Input:"
	@cat Inputs/input_1.txt
	@echo "\n\nTest Case 1 Output:"
	@cat result_1.txt
	@echo "\n\nTest Case 1 Expected Output:"
	@cat Outputs/output_1.txt

# Clean up generated files
.PHONY: clean
clean:
	rm -f result_*.txt Lab result_log_*.txt test_result
	clear

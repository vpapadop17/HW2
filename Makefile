all:
	g++ -std=c++17 -Wall TimeCode.cpp TimeCodeTests.cpp -o timecode_tests

run:
	./timecode_tests

try: all run

all:
	g++ -std=c++17 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -std=c++17 -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -std=c++17 -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt

run:
	./pdt

try: all run

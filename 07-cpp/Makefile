CXXFLAGS=-Wall -Wextra -pedantic -std=c++23

build: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

run: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp
	./main
	rm main

clean: main
	rm -f main
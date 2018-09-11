all: hello-cpp-world hello-c-world

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@


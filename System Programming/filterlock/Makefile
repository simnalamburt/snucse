all: filter sem

sem: sem.cc
	g++ $< -Wall -Wextra -O3 -std=c++11 -pthread -o $@

%: %.rs
	rustc $< -C opt-level=3

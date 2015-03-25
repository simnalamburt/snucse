all: error no-fma fma

error: error.rs
	rustc $< -o $@ -C opt-level=3 -C lto -C link-args=-s

CXXFLAGS = -std=c++11 -O3

no-fma: fma.cpp
	g++ $< -o $@ $(CXXFLAGS)
fma: fma.cpp
	g++ $< -o $@ $(CXXFLAGS) -mfma

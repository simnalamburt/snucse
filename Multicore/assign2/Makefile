all: error fma-y fma-n fma-error-y fma-error-n

error: error.rs
	rustc $< -o $@ -C opt-level=3

fma-n: fma.cpp
	g++ $< -o $@ -std=c++1y -O3
fma-y: fma.cpp
	g++ $< -o $@ -std=c++1y -O3 -mfma

fma-error-n: fma-error.c
	gcc $< -o $@ -std=c11 -O3
fma-error-y: fma-error.c
	gcc $< -o $@ -std=c11 -O3 -mfma

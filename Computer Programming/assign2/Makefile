BINS = 1.out 2.out
CXXFLAGS += -std=c++11 -O3

all: $(BINS)
%.out: 2013-11392-assign2-%-c11.o
	$(CXX) $< -o $@

clean:
	rm -f *.o $(BINS)

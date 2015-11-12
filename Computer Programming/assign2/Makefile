BINS = 1.out 2.out

all: $(BINS)

CXXFLAGS += -std=c++11

%.out: 2013-11392-assign2-%-c11.o
	$(CXX) $< -o $@

clean:
	rm -f *.o $(BINS)

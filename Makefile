ifdef version
  ifeq "$(version)" "pthreads"
    CXXFLAGS := -DENABLE_THREADS
    LDFLAGS := -pthread
  endif
endif

OBJS=CumNormalInv.o MaxFunction.o RanUnif.o nr_routines.o icdf.o \
	HJM_SimPath_Forward_Blocking.o HJM.o HJM_Swaption_Blocking.o  \
	main.o

BIN=bin

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o

.c.o:
	$(CXX) $(CXXFLAGS) -c $*.c -o $*.o

clean:
	rm -f *.o $(BIN)

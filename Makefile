ifdef version
  ifeq "$(version)" "pthreads"
    CXXFLAGS := -DENABLE_THREADS
    LDFLAGS := -pthread
  endif
endif

BIN=bin
all: $(BIN)
$(BIN): main.o CumNormalInv.o nr_routines.o icdf.o HJM_SimPath_Forward_Blocking.o HJM.o HJM_Swaption_Blocking.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o $(BIN)

CXXFLAGS = -W -Wall -Wextra -Wunused -Wunreachable-code -std=c++0x -g

ifdef version
  ifeq "$(version)" "pthreads"
    CXXFLAGS += -DENABLE_THREADS
    LDFLAGS += -pthread
  endif
endif

BIN=bin
all: $(BIN)
$(BIN): main.o helper.o hjm_path.o swaption.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o $(BIN)

CFLAGS = -W -Wall -Wextra -Wunused -Wunreachable-code -std=c99
CXXFLAGS = -W -Wall -Wextra -Wunused -Wunreachable-code -std=c++0x

ifdef version
  ifeq "$(version)" "cpu"
    CXXFLAGS += -DCPU
  endif
else
  LDFLAGS += -pthread
endif

BIN=bin
all: debug

release: CFLAGS += -O3
release: CXXFLAGS += -O3
release: $(BIN)

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: $(BIN)

$(BIN): main.o helper.o compute.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o $(BIN)

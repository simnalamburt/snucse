CFLAGS = -W -Wall -Wextra -Wunused -Wunreachable-code -std=c99
CXXFLAGS = -W -Wall -Wextra -Wunused -Wunreachable-code -std=c++0x
LDFLAGS = -lOpenCL

BIN=bin
all: release

release: CFLAGS += -O3
release: CXXFLAGS += -O3
release: $(BIN)

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: $(BIN)

$(BIN): main.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o $(BIN)

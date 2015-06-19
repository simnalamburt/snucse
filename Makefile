CXXFLAGS = -W -Wall -Wextra -Wunused -std=c++0x -O3
LDFLAGS = -lOpenCL

all: main.cc
	g++ $(CXXFLAGS) $(LDFLAGS) $^ -o bin
	strip bin

snucl: LDFLAGS += -I/opt/SnuCL/1.3.3/inc -L/opt/SnuCL/1.3.3/lib -lsnucl_cluster
snucl: main.cc
	mpic++ $(CXXFLAGS) $(LDFLAGS) $^ -o bin
	strip bin

CXX = g++
CXXFLAGS = -W -Wall -Wextra -Wunused -std=c++0x -O3
LDFLAGS = -lOpenCL
INPUT = main.cc

ifdef version
  ifeq "$(version)" "cpu"
    CXXFLAGS += -DUSE_CPU
    INPUT = cpu.cc
  endif
  ifeq "$(version)" "gpu"
  endif
  ifeq "$(version)" "mpi"
    CXX = mpic++
    CXXFLAGS += -DUSE_MPI
  endif
  ifeq "$(version)" "snucl"
    CXX = mpic++
    LDFLAGS += -I/opt/SnuCL/1.3.3/inc -L/opt/SnuCL/1.3.3/lib -lsnucl_cluster
  endif
endif

all:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INPUT) -o bin
	strip bin

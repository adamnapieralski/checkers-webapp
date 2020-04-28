ifdef OS
	EXT := .exe
else
	EXT :=
endif

CXX := g++
IDIR := .
ALLFLAGS := -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Wlogical-op \
	-Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast \
	-Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
	-Wstrict-overflow=5 -Wswitch-default -Wundef -Wshadow -Wnon-virtual-dtor
CPPFLAGS := -g -std=c++17 -I$(IDIR) -Wall -Wextra -pedantic $(ALLFLAGS)


source_files := $(filter-out src/CheckersPy.cc, $(wildcard src/*.cc))
header_files := $(wildcard src/*.h)
output_files := $(patsubst src/%.cc, build/%.o, $(source_files))

.PHONY: all run clean

all: build/main$(EXT);
	
run: build/main$(EXT)
	build/main$(EXT)

build/main$(EXT): $(output_files)
	$(CXX) $(CPPFLAGS) -o $@ $(output_files)

build/%.o: src/%.cpp $(header_files)
	$(CXX) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -f build/*

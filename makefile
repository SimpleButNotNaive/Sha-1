.PHONY: all run clean

CPP := $(wildcard *.cpp)
HPP := $(wildcard *.hpp)
CC := g++
FLAG := -g --std=c++14


all: main run

main: $(CPP) $(HPP)
	@$(CC) $(CPP) $(FLAG) -o $@

run: main
	@./main
clean:
	@rm -rf main
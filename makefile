CC = g++
CFLAGS = -Wall -Werror -pedantic -g
EXE = main
DEPS = main.cpp primes.cpp

all: $(EXE)

$(EXE): $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

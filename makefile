CC = g++
CFLAGS = -Wall -Werror -pedantic -g
EXE = main
DEPS = main.cpp primes.cpp
TDEPS = primes.cpp catch_amalgamated.cpp primes_test.cpp

mainexe: $(EXE)

$(EXE): $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

tests: $(TDEPS)
	$(CC) $(CFLAGS) -o tests $^ 
	./tests
#use del $(EXE).exe for windows
clean:
	rm $(EXE)
	

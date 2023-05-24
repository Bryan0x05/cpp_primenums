CC = g++
CFLAGS = -Wall -Werror -pedantic
EXE = multithread
LIBS = 
DEPS =
OBJS = 

all: $(EXE)

$(EXE): 
		$(CC) $(CFLAGS) -o $(EXE) multithread.cpp

clean:
		rm $(EXE) $(OBJS) 
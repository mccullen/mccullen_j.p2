# Name: Jeff McCullen and Emma Elliott
# Date: February 10, 2016
# Description: Tic-tac toe makefile

CC = g++
CFLAGS = -g -Wall

all: ticTacToe tests

ticTacToe: ticTacToe.o Board.o ComputerPlayer.o LCExceptions.o \
ConsoleInterface.o
	$(CC) $(CFLAGS) -o ticTacToe ticTacToe.o Board.o ComputerPlayer.o \
	LCExceptions.o ConsoleInterface.o

tests: tests.o Board.o ComputerPlayer.o LCExceptions.o \
ConsoleInterface.o
	$(CC) $(CFLAGS) -o tests tests.o Board.o ComputerPlayer.o \
	LCExceptions.o ConsoleInterface.o

tests.o: tests.cpp LCHashMap.h Board.h ComputerPlayer.h
	$(CC) $(CFLAGS) -c tests.cpp

ticTacToe.o: ticTacToe.cpp ConsoleInterface.h
	$(CC) $(CFLAGS) -c ticTacToe.cpp

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

ComputerPlayer.o: ComputerPlayer.cpp LCHashMap.h
	$(CC) $(CFLAGS) -c ComputerPlayer.cpp

LCExceptions.o: LCExceptions.cpp
	$(CC) $(CFLAGS) -c LCExceptions.cpp

ConsoleInterface.o: ConsoleInterface.cpp Board.h
	$(CC) $(CFLAGS) -c ConsoleInterface.cpp

clean:
	rm -f tests ticTacToe *.o *~

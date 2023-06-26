# Game of Cycles Program 
# https://github.com/BennTaylor/Game-of-Cycles
#
# 19-Jun-2023


OBJS	= \
	goc_game_tree.o \
	main.o

OUT	= main
CC	 = g++
FLAGS	 = -c -Wall -std=c++11
LFLAGS	 = 

all: main

main: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

debug: FLAGS += -DDEBUG -g --verbose
debug: LFAGS += --verbose
debug: all

verbose: FLAGS += --verbose
verbose: LFLAGS += --verbose
verbose: all

main.o: main.cpp goc_game_tree.h
	$(CC) $(FLAGS) main.cpp 

goc_game_tree.o: goc_game_tree.cpp
	$(CC) $(FLAGS) goc_game_tree.cpp 

clean:
	rm -f $(OBJS) $(OUT)

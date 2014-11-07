OBJS = cipher.cpp main.cpp analyst.cpp analyst.h

CC = g++

COMPILER_FLAGS = -w -std=c++11 -g

LINKER_FLAGS = 

OBJ_NAME = out

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)
	rm -rf out

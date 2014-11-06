OBJS = cipher.cpp main.cpp

CC = g++

COMPILER_FLAGS = -w -std=c++11

LINKER_FLAGS = 

OBJ_NAME = out

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

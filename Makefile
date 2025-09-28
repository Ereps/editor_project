SRC=src
INCLUDE=include
OBJ=obj
INSTALL=install
CC=gcc 
CFLAGS=-I$(INCLUDE) -Wall -Wextra -g 

all: build 

build: $(INSTALL)/main 

run: build
	@./$(INSTALL)/main

$(INSTALL)/main: $(OBJ)/main.o $(OBJ)/file_management.o $(OBJ)/key.o $(OBJ)/input.o $(OBJ)/cursor.o 
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	@rm -f $(OBJ)/*.o $(INSTALL)/*

.PHONY= clean all build

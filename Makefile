SRC=src
INCLUDE=include
OBJ=obj
INSTALL=install
CC=gcc
CFLAGS=-I$(INCLUDE)

all: build 

build: $(INSTALL)/test 

run: build
	@./$(INSTALL)/test

$(INSTALL)/test: $(OBJ)/test.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	@rm -f $(OBJ)/*.o $(INSTALL)/*

.PHONY= clean all build

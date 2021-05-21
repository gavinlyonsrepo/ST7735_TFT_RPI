CC=gcc
LDFLAGS= -lbcm2835 -lrt
CFLAGS = -Iinclude/  -c -Wall 
MD=mkdir

SRC=src
OBJ=obj
SRCS = $(wildcard $(SRC)/*.c)
HDRS=$(wildcard  $(HDR)/*.h)
OBJS = $(patsubst $(SRC)/%.c,  $(OBJ)/%.o, $(SRCS))
BIN=./bin
TARGET=$(BIN)/test

all: pre-build $(TARGET) 

run:
	sudo $(TARGET) 
	
pre-build:
	@echo 'START!'
	$(MD) -vp $(BIN)
	$(MD) -vp $(OBJ)


$(TARGET): $(OBJS) $(OBJ)
	@echo 'MAKE EXE FILE'
	$(CC)  $(OBJS) -o $@ $(LDFLAGS)
	@echo 'DONE!'

$(OBJ)/%.o :  $(SRC)/%.c   $(OBJ) 
	@echo 'MAKE OBJECT FILE'
	$(CC) $(CFLAGS) $< -o  $@ 

clean:
	@echo 'CLEANUP!'
	rm -vf  $(OBJS) $(TARGET)
	@echo 'DONE!'




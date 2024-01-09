# Gavin lyons 06-2021 
# Makefile to build example program for ST7735_TFT_RPI library.
# URL: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI

# === Options ===
# 1. make = create test file at bin/test from src/main.cpp , 
# 2. make clean = deletes .o files generated (by step 1) from build directory
# 3. make run = run test file (made by step 1), "sudo bin/test"
# ==============

# ************************************************
# User SRC directory Option Section
# Pick ONE example "SRC" dir and ONE ONLY.
# Comment out the others. #

SRC=src/Hello_world
#SRC=src/Hello_world_SWSPI
#SRC=src/Text_Tests
#SRC=src/Graphic_Tests
#SRC=src/Function_Tests
#SRC=src/Bitmap_Tests
#SRC=src/Frame_rate_test
#SRC=src/Frame_rate_test_2
# ************************************************

# lang c plus plus
CC=g++
# Linker flags :: note -lrt onyl needed for Bitmap and FPS examples
LDFLAGS= -lbcm2835 -lrt -lST7735_TFT_RPI
# Complier flags
CFLAGS = -Iinclude/  -c -Wall 

MD=mkdir
# Complier Directories
OBJ=obj
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,  $(OBJ)/%.o, $(SRCS))

# Executable path
BIN=./bin
TARGET=$(BIN)/exampleTest.out

all: clean pre-build $(TARGET) 

run:
	sudo $(TARGET) 


pre-build:
	@echo '***************'
	@echo 'START!'
	$(MD) -vp $(BIN)
	$(MD) -vp $(OBJ)


$(TARGET): $(OBJS) $(OBJ)
	@echo 'MAKE EXE FILE'
	$(CC)  $(OBJS) -o $@ $(LDFLAGS)
	@echo 'DONE!'
	@echo '***************'

$(OBJ)/%.o :  $(SRC)/%.cpp   $(OBJ) 
	@echo 'MAKE OBJECT FILE'
	$(CC) $(CFLAGS) $< -o  $@ 

clean:
	@echo '***************'
	@echo 'CLEANUP!'
	rm -vf  $(OBJS) $(TARGET)
	@echo 'DONE!'
	@echo '***************'



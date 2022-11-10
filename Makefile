CC = g++
INCLUDE_PATH = /usr/local/Cellar/sfml/2.5.1_2
LIB_PATH = /usr/local/Cellar/sfml/2.5.1_2/lib
PROJECT_NAME = aa
CFLAGS = -std=c++2b -I$(INCLUDE_PATH) -L$(LIB_PATH) -lsfml-graphics -lsfml-window -lsfml-system
PROJECT_FILES = src/*.cpp src/player/*.cpp src/item/*.cpp src/grid/*.cpp 

make:
	$(CC) $(PROJECT_FILES) -o $(PROJECT_NAME) $(CFLAGS)

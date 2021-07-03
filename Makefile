CC = g++
CCPARAMS = -pipe -O2

LIBARIES = -lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRC_DIR = src/
OBJECT_DIR = build/object_files/
MODULES = $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)Mapper/*.cpp)
OBJECTS = $(wildcard $(OBJECT_DIR)*.o)
OUTPUT_DIR = build/


all: $(MODULES)
	clear
	$(CC) $(CCPARAMS) -Isrc $^ -o $(OUTPUT_DIR)NES $(LIBARIES)

debug: $(MODULES)
	clear
	$(CC) -g $(CCPARAMS) -Isrc $^ -o $(OUTPUT_DIR)NES $(LIBARIES)

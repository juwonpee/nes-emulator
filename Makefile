CC = g++
CC_INCLUDE = src/
CCFLAGS = -pipe -O2
CCFLAGS_DEBUG = -g -pipe -Og

LIBARIES = -lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRC_DIR = src/
OBJECT_DIR = build/object_files/
OUTPUT = build/NES
MODULES = $(wildcard $(SRC_DIR)*.cpp)
MODULES := $(notdir $(MODULES))
OBJECTS = $(wildcard $(OBJECT_DIR)*.o)



all: $(MODULES)
	clear
	$(CC) $(OBJECTS) -o $(OUTPUT) $(LIBARIES)

%.cpp:
	$(CC) $(CCFLAGS_DEBUG) -I$(CC_INCLUDE) -c $(SRC_DIR)$@ -o $(OBJECT_DIR)$(addsuffix .o,$(basename $@))


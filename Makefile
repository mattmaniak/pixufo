TARGET = pixufo

CC = g++
CXXFLAGS = -Wall -Wextra -lSDL2

SRC_DIR = game/src

all:
	g++ $(SRC_DIR)/$(TARGET).cpp -o $(TARGET) \
	$(CXXFLAGS)

TARGET = pixufo

CC = g++
CXXFLAGS = -Wall -Wextra -lsfml-graphics -lsfml-system -lsfml-window

SRC_DIR = game/src

all:
	g++ $(SRC_DIR)/$(TARGET).cpp -o $(TARGET) \
	$(CXXFLAGS)

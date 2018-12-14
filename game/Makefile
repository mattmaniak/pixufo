TARGET = pixufo

CC = g++
CXXFLAGS = -Wall -Wextra -lSDL2

SRC_DIR = src

RM = rm -rf

all:
	g++ $(SRC_DIR)/$(TARGET).cpp -o $(TARGET) \
	$(CXXFLAGS)

.PHONY: clean

clean:
	$(RM) $(TARGET)

TARGET = pixufo

CC = g++

WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
-Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline \
-Wno-long-long -Wconversion

CXXFLAGS = -lSDL2 $(WARNINGS)

SRC_DIR = src

RM = rm -rf

all:
	$(CC) $(SRC_DIR)/$(TARGET).cpp -o $(TARGET) \
	$(CXXFLAGS)

.PHONY: clean

clean:
	$(RM) $(TARGET)

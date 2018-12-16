TARGET = pixufo

CC = g++

WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
-Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
-Wold-style-cast -Woverloaded-virtual  -Wredundant-decls -Wshadow \
-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wswitch-default -Wundef -Werror -Wno-unused

CXXFLAGS = -lSDL2 $(WARNINGS)

SRC_DIR = src

RM = rm -rf

all:
	$(CC) $(SRC_DIR)/$(TARGET).cpp -o $(TARGET) \
	$(CXXFLAGS)

.PHONY: clean

clean:
	$(RM) $(TARGET)

TARGET = PixUfo

CC = g++
CXXWARNINGS = -Wall -Wextra -pedantic

CXXFLAGS = -I$(INC_DIR) -std=c++11 -lSDL2 $(CXXWARNINGS)
DEBUGFLAGS =

ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
-fsanitize-address-use-after-scope -fsanitize-undefined-trap-on-error \
-fstack-protector-all

INC_DIR = $(SRC_DIR)/include
SRC_DIR = src
OBJ_DIR = obj

# All in the ./obj depending on the ./src.
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# Compilation of object files depends on source files wnich depends on headers.
# "$@" - alias to name on the left of ':', "$^" - on the right.
# "$<" is a first item in the dependencies list.
# "-c" generates the object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< \
	$(CXXFLAGS) \

# Builds the binary by linking object files.
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ \
	$(CXXFLAGS) \
	$(DEBUGFLAGS)

address: DEBUGFLAGS = $(ASAN_FLAGS)
address: $(TARGET)

.PHONY: clean

clean:
	$(RM) $(TARGET) $(OBJ_DIR)/*

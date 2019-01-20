TARGET =

CC = g++
CXXFLAGS = -std=c++11 -O3 -Wall -Wextra -pedantic
LDFLAGS = -lSDL2

SRC_DIR = src
OBJ_DIR = obj

MKDIR_OBJ =

ifeq ($(OS), Windows_NT)
	TARGET = PixUfo.exe
	LDFLAGS += -lmingw32 -mwindows -mconsole -lSDL2main
	MKDIR_OBJ = if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
else
	TARGET = PixUfo
	MKDIR_OBJ = mkdir -p $(OBJ_DIR)
endif

# All in the ./obj depending on the ./src.
OBJS = $(patsubst $(SRC_DIR)/%.cpp, \
       $(OBJ_DIR)/%.o, \
       $(wildcard $(SRC_DIR)/*.cpp))

# Compilation of object files depends on source files wnich depends on headers.
# "$@" - alias to name on the left of ':', "$^" - on the right.
# "$<" is a first item in the dependencies list.
# "-c" generates the object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(MKDIR_OBJ)
	$(CC) -c -o $@ $< \
	$(CXXFLAGS) \

# Builds the binary by linking object files.
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ \
	$(CXXFLAGS) \
	$(LDFLAGS)

.PHONY: clean

ifeq ($(OS), Windows_NT)
clean:
	del $(TARGET)
	rmdir /Q /S $(OBJ_DIR)
else
clean:
	$(RM) -r $(TARGET) $(OBJ_DIR)
endif

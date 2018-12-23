TARGET = pixufo

CC = g++
CXXWARNINGS = -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wsign-promo \
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Werror \
-Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wundef \
-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wno-unused \
-Wsign-conversion -Wswitch-default -Wstrict-null-sentinel -Wstrict-overflow=5

CXXFLAGS = -std=c++98 -lSDL2 $(CXXWARNINGS)
DEBUGFLAGS =

ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
-fsanitize-address-use-after-scope -fsanitize-undefined-trap-on-error \
-fstack-protector-all

SRC_DIR = src
OBJ_DIR = obj

# All in the ./obj depending on the ./src.
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# Compilation of object files depends on source files wnich depends on headers.
# "$@" - alias to name on the left of ':', "$^" - on the right.
# "$<" is a first item in the dependencies list.
# "-c" generates the object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
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
	$(RM) -r $(TARGET) $(OBJ_DIR)

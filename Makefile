TARGET =

CC = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic
IFLAGS =
LDFLAGS = -lSDL2 -lSDL2_ttf
ASAN_FLAGS =

SRC_DIR = src
OBJ_DIR = obj

MKDIR_OBJ =

ifeq ($(OS), Windows_NT)
	TARGET = PixUfo.exe
	LDFLAGS += -lmingw32 -mwindows -lSDL2main
	MKDIR_OBJ = if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

else ifeq ($(shell uname), Darwin)
	TARGET = PixUfo
	ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-fsanitize-undefined-trap-on-error -fstack-protector-all

	IFLAGS += -I $(wildcard /opt/homebrew/Cellar/sdl2/*/include/SDL2)
	IFLAGS += -I $(wildcard /opt/homebrew/Cellar/sdl2_ttf/*/include)

	LDFLAGS += -L $(wildcard /opt/homebrew/Cellar/sdl2/*/lib)
	LDFLAGS += -L $(wildcard /opt/homebrew/Cellar/sdl2_ttf/*/lib)

	# sdl2-config --static-libs but modified a little.
	LDFLAGS += -L/opt/homebrew/lib /opt/homebrew/lib/libSDL2.a -lm -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-weak_framework,CoreHaptics -Wl,-weak_framework,GameController -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal

	MKDIR_OBJ = mkdir -p $(OBJ_DIR)

else ifeq ($(shell uname), Linux)
	TARGET = PixUfo
	ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-fsanitize-undefined-trap-on-error -fstack-protector-all

	MKDIR_OBJ = mkdir -p $(OBJ_DIR)
endif

# All in the ./obj depending on the ./src.
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, \
       $(wildcard $(SRC_DIR)/*.cpp))

# Compilation of object files depends on source files wnich depends on headers.
# "$@" - alias to name on the left of ':', "$^" - on the right.
# "$<" is a first item in the dependencies list.
# "-c" generates the object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(MKDIR_OBJ)
	$(CC) -c -o $@ $< \
	$(IFLAGS) \
	$(CPPFLAGS) 


bundle_contents = PixUfo.app/Contents

# Builds the binary by linking object files.
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ \
	$(CPPFLAGS) \
	$(LDFLAGS)

bundle: $(TARGET)
	mkdir -p $(bundle_contents)/MacOS
	mkdir -p $(bundle_contents)/Resources
	cp Info.plist $(bundle_contents)/Info.plist
	echo "APPL????" > $(bundle_contents)/PkgInfo
	cp $(TARGET) $(bundle_contents)/MacOS/
	# $(INSTALL_PROGRAM) $< $(bundle_contents)/MacOS/

.PHONY: debug
debug: CPPFLAGS += -DDEBUG
debug: LDFLAGS += $(ASAN_FLAGS)
debug: $(TARGET)

.PHONY: clean
ifeq ($(OS), Windows_NT)
clean:
	del $(TARGET)
	rmdir /Q /S $(OBJ_DIR)
else
clean:
	$(RM) -r $(TARGET) $(OBJ_DIR)
endif

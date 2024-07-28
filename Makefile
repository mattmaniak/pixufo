TARGET =

CC = g++
CPPFLAGS = -std=c++20 -Wall -Wextra -pedantic
IFLAGS =
LDFLAGS = -lSDL2 -lSDL2_ttf
ASAN_FLAGS =
GCOV_FLAGS =

SRC_DIR = src
OBJ_DIR = obj

MKDIR_OBJ =

ifeq ($(OS), Windows_NT)
	TARGET = PixUfo.exe
	LDFLAGS += -lmingw32 -mwindows -lSDL2main
	MKDIR_OBJ = if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

else ifeq ($(shell uname), Darwin)
	TARGET = PixUfo

	ASAN_FLAGS = -fsanitize=address -fsanitize=undefined \
	-fsanitize-undefined-trap-on-error -fstack-protector-all
	GCOV_FLAGS = -ftest-coverage -fprofile-arcs

	# Output of sdl2-config --cflags.
	IFLAGS += -I /opt/homebrew/include/SDL2 -D_THREAD_SAFE

	LDFLAGS += -L /opt/homebrew/lib /opt/homebrew/lib/libSDL2.a -lm -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-weak_framework,CoreHaptics -Wl,-weak_framework,GameController -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal

	MKDIR_OBJ = mkdir -p $(OBJ_DIR)

else ifeq ($(shell uname), Linux)
	TARGET = PixUfo

	GCOV_FLAGS = -ftest-coverage -fprofile-arcs
	ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-fsanitize-undefined-trap-on-error -fstack-protector-all

	MKDIR_OBJ = mkdir -p $(OBJ_DIR)
endif

# All in the ./obj depending on the ./src.
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, \
       $(wildcard $(SRC_DIR)/*.cc))

# Compilation of object files depends on source files wnich depends on headers.
# "$@" - alias to name on the left of ':', "$^" - on the right.
# "$<" is a first item in the dependencies list.
# "-c" generates the object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/%.h
	$(MKDIR_OBJ)
	$(CC) -c -o $@ $< \
	$(IFLAGS) \
	$(CPPFLAGS) 
	@echo ' '

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
debug: CPPFLAGS += -DDEBUG $(GCOV_FLAGS)
debug: LDFLAGS += $(ASAN_FLAGS)
debug: $(TARGET)

.PHONY: lint
lint:
	cpplint src/*

.PHONY: clean
ifeq ($(OS), Windows_NT)
clean:
	del $(TARGET)
	rmdir /Q /S $(OBJ_DIR)

else ifeq ($(shell uname), Darwin)
clean:
	$(RM) -r $(TARGET) $(TARGET).app $(OBJ_DIR)
else
clean:
	$(RM) -r $(TARGET) $(OBJ_DIR)
endif

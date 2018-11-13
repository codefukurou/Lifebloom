MKDIR := mkdir -p
CPP := g++
SRC_DIR := src
OBJ_DIR := bin/obj
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lGL -lGLU -lglut -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
CPPFLAGS := -Isrc -Iinclude -Iinclude/rapidjson/include -Wall -std=c++17 -O2 -g -pedantic

all: directory $(BIN_DIR)/main.out

directory:
	$(MKDIR) $(BIN_DIR)
	$(MKDIR) $(OBJ_DIR)

$(BIN_DIR)/main.out: $(OBJ_FILES)
	$(CPP) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(RM) -r $(BIN_DIR)



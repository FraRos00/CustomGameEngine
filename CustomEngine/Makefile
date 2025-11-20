CXX := g++

#Per sviluppo
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -MMD -MP
# Per rilascio
# CXX_FLAGS := -std=c++17 -Iinclude -MMD -MP -O2

# Per Windows
ifeq ($(OS),Windows_NT)
	LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm -lwaylandscale
else
# Per linux
	LIBS := -lraylib -lglfw -lm -ldl -lpthread -lrt -lwaylandscale -lwayland-client
endif

LDFLAGS := -Llib

SRC_DIR := src
BUILD_DIR := build
BIN := game.exe

# --- Trova i sorgenti .cpp ---

SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:.o=.d)

# --- Compilazione finale

$(BIN): $(OBJ)
	@echo "Linking..."
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)
	@echo "Build completed: $(BIN)"

# --- Compilazione singoli file

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(BIN)
	@echo "Done"

run: $(BIN)
	@echo "Starting the game..."
	./$(BIN)

.PHONY: clean run

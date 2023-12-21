SRC_DIR := src
OBJ_DIR := obj
TARGET_DIR := bin
TARGET := $(TARGET_DIR)/mv
COMPILER := g++

# Find all .cpp files in subdirectories of SRC_DIR
SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Generate object file paths based on source file paths
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(SRC_FILES))

CFLAGS := -Wall -Wextra -ggdb -fsanitize=address -pedantic
CFLAGS := -Wall -Wextra -ggdb -pedantic
LIBS :=

all: $(TARGET)

# Include dependency files
-include $(DEP_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -MMD -c $< -o $@

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) $^ -o $@ $(LIBS)

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET_DIR)

.PHONY: all run clean


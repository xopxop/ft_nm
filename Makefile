# Program name
TARGET := ft_nm

# Build command
CC := clang
CFLAGS :=
# CFLAGS := -Wall -Wextra -Werror
DEBUG := -g

# File structure
OBJ_DIR := obj
SRC_DIR := src

# Source files
SRC_FILES += $(SRC_DIR)/ft_nm.c

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)
	@echo "✅ Build completed!"

# Build target
$(TARGET): mkdir $(OBJ_FILES)
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_FILES))) -o $(TARGET)

# Create object directory
mkdir:
	@mkdir -p $(OBJ_DIR)

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | mkdir
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(notdir $@)

# Clean up
clean:
	@rm -rf $(OBJ_DIR)

# Clean up and remove target
fclean: clean
	@echo "🧹 Cleaning up..."
	@rm -rf $(TARGET)
	@echo "🧼 Clean complete!"

# Rebuild
re: fclean all

.PHONY: all mkdir clean fclean re
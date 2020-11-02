# Directories info
SRC_DIR   := ./
BIN_DIR   := ./
INC_DIR   := ./
OBJ_DIR   := ./

# Compiler info
CC        := gcc
CFLAGS    := -Wall -Werror -std=c11 -ggdb3
LDLIBS    := -lm
IFLAGS    := -I$(INC_DIR)

# make info
TARGET    := $(BIN_DIR)/main
SOURCES   := $(wildcard $(SRC_DIR)/*.c)
OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

.PHONY: all run clean clean_dep
all: $(TARGET) clean clean_dep

# Dependency files info
DEPS = $(patsubst $(OBJ_DIR)/%.o,$(OBJ_DIR)/%.d,$(OBJECTS))
-include $(DEPS)
DFLAGS    = -MMD -MF $(@:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@ $(DFLAGS)

run:
	@$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o

clean_dep:
	rm -f $(OBJ_DIR)/*.d

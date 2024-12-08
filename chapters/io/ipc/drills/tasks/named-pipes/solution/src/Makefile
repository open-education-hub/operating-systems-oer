# Get the relative path to the directory of the current makefile
MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
INCLUDES_DIR := $(MAKEFILE_DIR)
UTILS_DIR := $(MAKEFILE_DIR)/utils

# Compiler and flags
CPPFLAGS += -I$(INCLUDES_DIR)
CFLAGS += -g -Wall -Wextra
LDFLAGS += -z lazy

# Logger object
LOGGER_DIR := $(UTILS_DIR)/log
LOGGER_OBJ = log.o
LOGGER = $(LOGGER_DIR)/$(LOGGER_OBJ)

# Source files and corresponding binaries
BINARIES = named_pipe
SRCS = $(BINARIES:=.c)
OBJS = $(SRCS:.c=.o)

# Default rule: build all binaries
all: $(BINARIES)

# Rule to compile the binaries
$(BINARIES): %: %.o $(LOGGER)
	$(CC) $(LDFLAGS) $^ -o $@

# Rule to compile the logger object
$(LOGGER): $(LOGGER_DIR)/log.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Clean rule: Remove object files and binaries
clean:
	-rm -f $(OBJS) $(BINARIES)
	-rm -f $(LOGGER)
	-rm -f my-fifo

.PHONY: all clean

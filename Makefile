# Compiler and flags
CC      = clang
CFLAGS  = -Wall -O2 -fopenmp -lomp
TARGET  = openmp_sort
SRCS    = main.c mergesort.c test.c
OBJS    = $(SRCS:.c=.o)

# If DEBUG is enabled, define it and change binary name
ifdef DEBUG
    CFLAGS += -DDEBUG
    TARGET := $(TARGET)_debug
endif

.PHONY: all debug clean test benchmark run

# Default build
all: $(TARGET)

# Debug build
debug:
	$(MAKE) DEBUG=1

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run in test mode (default)
test: $(TARGET)
	./$(TARGET)

# Run in benchmark mode
benchmark: $(TARGET)
	./$(TARGET) benchmark

# General run (alias for test)
run: test

# Cleanup
clean:
	rm -f *.o openmp_sort openmp_sort_debug

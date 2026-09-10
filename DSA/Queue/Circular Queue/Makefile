CXX ?= g++

SOURCE := circular_queue.cc
HEADER := circular_queue.h
COMMON_HEADER := ..\..\Common\logger.h
TARGET := circular_queue
DEBUG_TARGET := circular_queue_debug
ASAN_TARGET := circular_queue_asan
PERF_TARGET := circular_queue_perf
LOG_FILE := circular_queue.log

COMMON_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic
INCLUDE_FLAGS := -I../../Common
RELEASE_FLAGS := $(COMMON_FLAGS) -O2
DEBUG_FLAGS := $(COMMON_FLAGS) -O0 -g -DDEBUG
ASAN_FLAGS := $(DEBUG_FLAGS) -fsanitize=address,undefined -fno-omit-frame-pointer
PERF_FLAGS := $(COMMON_FLAGS) -O3 -DNDEBUG

.PHONY: all debug asan perf run run-debug run-asan run-perf clean

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER) $(COMMON_HEADER)
	$(CXX) $(RELEASE_FLAGS) $(INCLUDE_FLAGS) $< -o $@

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SOURCE) $(HEADER) $(COMMON_HEADER)
	$(CXX) $(DEBUG_FLAGS) $(INCLUDE_FLAGS) $< -o $@

asan: $(ASAN_TARGET)

$(ASAN_TARGET): $(SOURCE) $(HEADER) $(COMMON_HEADER)
	$(CXX) $(ASAN_FLAGS) $(INCLUDE_FLAGS) $< -o $@

perf: $(PERF_TARGET)

$(PERF_TARGET): $(SOURCE) $(HEADER) $(COMMON_HEADER)
	$(CXX) $(PERF_FLAGS) $(INCLUDE_FLAGS) $< -o $@

run: all
	./$(TARGET)

run-debug: debug
	./$(DEBUG_TARGET)

run-asan: asan
	./$(ASAN_TARGET)

run-perf: perf
	./$(PERF_TARGET)

clean:
	-del /Q $(TARGET) $(DEBUG_TARGET) $(ASAN_TARGET) $(PERF_TARGET) $(LOG_FILE) 2>NUL

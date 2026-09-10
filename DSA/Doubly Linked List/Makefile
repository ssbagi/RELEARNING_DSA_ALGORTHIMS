CXX ?= g++

SOURCE := double_linked_list.cc
HEADER := double_linked_list.h
COMMON_HEADER := ..\Common\logger.h
TARGET := double_linked_list
DEBUG_TARGET := double_linked_list_debug
ASAN_TARGET := double_linked_list_asan
PERF_TARGET := double_linked_list_perf
LOG_FILE := double_linked_list.log

COMMON_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic
INCLUDE_FLAGS := -I../Common
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

# Linked List

A small C++ linked-list exercise for revisiting node creation, insertion, traversal, search, deletion, and basic program execution. The demo creates a head node with `100`, inserts ten more nodes, searches for two values, deletes two values, and traverses the list before and after deletion.

## Basic API

The list node and insertion declaration are available from `linked_list.h`:

```cpp
#include "linked_list.h"

Node head;
head.data = 100;
insert_node(head, 200);
```

`insert_node()` takes a pointer to an existing list node and appends a new node at the tail. The caller owns the dynamically allocated nodes and must release them when the list is no longer needed.

## Contents

- `linked_list.cc`: Linked-list example program.
- `linked_list.h`: Reusable `Node` declaration.
- `Makefile`: Release, debug, and sanitizer build targets.
- `linked_list.log`: Timestamped runtime log generated when the program runs.
- `../Common/logger.h`: Shared header-only logger for all DSA examples.

## Shared Logger

The reusable logger is kept in `DSA/Common/logger.h`. Include it from another DSA program and create a logger for that program's log file:

```cpp
#include "logger.h"

common::Logger logger("my_algorithm.log");
logger.info("Value = ", value, ", index = ", index);
logger.error("Input is invalid");
logger.fatal("Cannot continue");
```

The logger is header-only and uses a variadic STL-style template, so strings, integers, and other streamable values can be passed directly without manually converting them to strings. Each DSA folder should add `-I../Common` to its compiler flags and list `../Common/logger.h` as a Makefile dependency.

## Prerequisites

Install the following tools and make sure they are available on `PATH`:

- A C++17 compiler, such as `g++`.
- GNU Make.
- Optional: `gdb` for interactive debugging.
- Optional: AddressSanitizer and UndefinedBehaviorSanitizer runtimes for `make asan`.

Check the tools from PowerShell or a terminal:

```powershell
g++ --version
make --version
gdb --version
```

The `gdb` command is optional and may not be installed.

## Build With Make

Run these commands from this directory:

```text
make all
make debug
make asan
make perf
```

The targets produce separate executables:

| Target | Executable | Purpose |
| --- | --- | --- |
| `all` | `linked_list` | Optimized build with warnings enabled |
| `debug` | `linked_list_debug` | Debug symbols, no optimization, and `DEBUG` defined |
| `asan` | `linked_list_asan` | AddressSanitizer and UndefinedBehaviorSanitizer |
| `perf` | `linked_list_perf` | Performance-oriented build with stronger optimization |

`make all` is the default release-style build. The compiler flags are defined in the Makefile:

- Common: `-std=c++17 -Wall -Wextra -Wpedantic`
- Release: `-O2`
- Debug: `-O0 -g -DDEBUG`
- Sanitizers: `-fsanitize=address,undefined -fno-omit-frame-pointer`
- Performance: `-O3 -DNDEBUG`

The performance profile is intended for benchmarking or checking optimized behavior. It removes debug assertions through `NDEBUG` and prioritizes optimization over debugging visibility. The `-O3` profile is portable, but benchmark results can still vary by compiler, operating system, and CPU.

## Run The Program

Use the Makefile run targets:

```text
make run
make run-debug
make run-asan
make run-perf
```

Expected output:

```text
The New Element added to the Linked List is : 100
```

Each run also appends timestamped events to `linked_list.log`. The log includes program startup, node creation, printed output, successful completion, and runtime errors. Earlier runs are preserved until `make clean` is used.

The logger is intentionally small and uses direct severity calls:

```cpp
logger.info("Node created");
logger.error("Node data is invalid");
logger.fatal("Unable to open log file");
```

`info()` records normal events, `error()` records recoverable problems, and `fatal()` records an unrecoverable problem, prints it to `stderr`, and terminates the program. No `try`/`catch` flow is required for this basic example.

You can also run the executables directly after building them:

```text
./linked_list
./linked_list_debug
./linked_list_asan
./linked_list_perf
```

On PowerShell, the equivalent direct command is:

```powershell
.\linked_list.exe
```

## Compile Without Make

The program can be compiled directly when Make is unavailable:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 linked_list.cc -o linked_list.exe
```

Debug build:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g -DDEBUG linked_list.cc -o linked_list_debug.exe
```

Performance build:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -O3 -DNDEBUG linked_list.cc -o linked_list_perf.exe
```

Sanitizer build:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g -DDEBUG `
    -fsanitize=address,undefined -fno-omit-frame-pointer `
    linked_list.cc -o linked_list_asan.exe
```

The sanitizer command requires a compiler toolchain that provides the sanitizer runtime libraries. If the linker reports that it cannot find `libasan` or `libubsan`, install a complete sanitizer-enabled toolchain or use a compiler distribution that includes those libraries.

## Debugging With GDB

Build the debug executable first:

```text
make debug
gdb ./linked_list_debug
```

Useful GDB commands:

```text
break main
run
next
print new_node->data
continue
quit
```

On Windows, use the executable name generated by your toolchain if it includes `.exe`:

```text
gdb .\linked_list_debug.exe
```

## Clean Build Outputs

Remove all generated executables with:

```text
make clean
```

The clean target uses the Windows `del` command. If using a Unix-like shell, remove the files manually if needed:

```text
rm -f linked_list linked_list_debug linked_list_asan linked_list_perf linked_list.log
```

## Current Learning Scope

The current program is intentionally minimal. Suggested next steps are:

1. Add a constructor for `Node`.
2. Add insertion at the front and back.
3. Add traversal through all nodes.
4. Add search and deletion operations.
5. Release allocated nodes and verify the program with the sanitizer build.
6. Add focused tests for empty, single-node, and multi-node lists.

# Stack using an array

A fixed-size stack. The capacity is decided once in `create_stack()` and never changes, so the storage is allocated a single time instead of once per element.

## State

- `items` — contiguous storage of exactly `capacity` integers.
- `top` — index of the top element.
- `top == -1` means empty; `top == capacity - 1` means full.

## Operations

| Stack operation | Function           | Time |
| --------------- | ------------------ | ---- |
| `push()`        | `push_element()`   | O(1) |
| `pop()`         | `pop_element()`    | O(1) |
| `top()`         | `peek_element()`   | O(1) |
| size            | `stack_size()`     | O(1) |
| search          | `search_element()` | O(n) |

`push_element` returns `false` on overflow and `pop_element` returns `false` on underflow, since neither condition can be resolved by growing the array.

`pop_element` does not clear the vacated slot; lowering `top` is enough to make it unreachable, and the next `push` overwrites it.

## Trade-off against the linked-list stack

- Array: O(1) push and pop, no per-element allocation, better cache locality, but the capacity is a hard limit.
- Linked list: unbounded size, but one allocation per element and an extra traversal to reach the top.

## Build and run

```
make clean
make all
make run
```

Other targets: `debug`, `asan`, `perf`, and the matching `run-*` targets. Output is logged to `stack_array.log`.

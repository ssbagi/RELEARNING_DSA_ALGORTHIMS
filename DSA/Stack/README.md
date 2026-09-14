# Stack

A stack is a LIFO container: the element inserted last is the element removed first.

## Implementations

- **Linked-list stack** (this folder): dynamic size, one node allocated per `push`, no fixed capacity.
- **Array stack** (`Stack Array/`): fixed capacity chosen at creation, memory allocated once, `push` fails on overflow.

## Linked-list stack

Built on a doubly linked list. The last node is the top of the stack.

| Stack operation | Function        | Time |
| --------------- | --------------- | ---- |
| `push()`        | `insert_node()` | O(n) |
| `pop()`         | `delete_node()` | O(n) |
| `top()`         | `peek_node()`   | O(n) |
| search          | `search_node()` | O(n) |
| size            | `stack_size()`  | O(n) |

`push` and `pop` are O(n) because the list is walked from the bottom node to reach the last node. Keeping a separate tail pointer would make both O(1), at the cost of one more pointer to maintain.

`delete_node` writes the removed value through `popped_data` and returns the updated bottom node, which is `nullptr` once the final node is removed.

## Build and run

```
make clean
make all
make run
```

Other targets: `debug`, `asan`, `perf`, and the matching `run-*` targets. Output is logged to `stack.log`.

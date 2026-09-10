## Mistake Learning

This queue is implemented as a circular linked-list queue, not as a fixed-size circular array.

- Linked-list circular queue: dynamic size, nodes are created and deleted as needed, and there is no fixed capacity requirement.
- Array-based circular queue: fixed capacity, memory is allocated once, and the `front` and `rear` indices wrap around the array.
- The core concept is still circular behavior, but the underlying data structure is different.
- A capacity-based "hack" is appropriate only when the implementation is deliberately fixed-size; it is not the same as a dynamic queue.

This distinction is important because the linked-list version can grow dynamically, while the array version cannot grow beyond its allocated size.

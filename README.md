## Building Blocks from Scratch: Understanding Arrays with a Pythonic Lens

Hey everyone! 👋

We've been exploring the fundamental concepts of Data Structures and Algorithms, and today, we're going to get our hands a little "dirtier" by looking at how an array, one of the most basic yet crucial data structures, can be implemented from the ground up. Forget the built-in lists for a moment; we're going to build our own simplified version in Python to truly understand what's happening under the hood.

The code snippet we'll be dissecting provides a fascinating glimpse into the mechanics of a dynamic array. Let's break it down step by step.

### 🛠️ Our DIY Array: The `RawArray` Class

The code defines a class called `RawArray`. Think of this as our blueprint for creating array-like objects.

```python
from ctypes import *

class RawArray:
    def __init__(self, element_type, initial_capacity=2):
        self.element_type = element_type
        self.capacity = initial_capacity
        self.size = 0
        self.data = (self.element_type * self.capacity)()  # malloc
```

* **`from ctypes import *`**: This line imports the `ctypes` module, which provides low-level array creation capabilities similar to what you might find in languages like C. It allows us to allocate raw memory.
* **`__init__(self, element_type, initial_capacity=2)`**: This is the constructor of our `RawArray`. When we create a `RawArray` object, we need to specify:
    * `element_type`: The type of data this array will hold (e.g., `c_int` for integers). This enforces that all elements in our array will be of the same type, a characteristic of traditional arrays.
    * `initial_capacity`: The initial number of elements our array can store. It defaults to 2.
    * Inside the constructor:
        * `self.element_type = element_type`: We store the specified element type.
        * `self.capacity = initial_capacity`: We store the current maximum capacity of our array.
        * `self.size = 0`: We keep track of the number of elements currently stored in the array, which starts at zero.
        * `self.data = (self.element_type * self.capacity)()`: This is the crucial line! It uses `ctypes` to allocate a contiguous block of memory capable of holding `self.capacity` elements of the specified `self.element_type`. This is analogous to using `malloc` in C to reserve memory.

### ⚙️ Growing on Demand: The `_resize` Method

One of the key features of dynamic arrays (like Python lists) is their ability to grow in size as needed. Our `RawArray` implements this with the `_resize` method:

```python
    def _resize(self):
        print(f"Resizing from {self.capacity} to {self.capacity * 2}")
        new_capacity = self.capacity * 2
        new_data = (self.element_type * new_capacity)()
        # Simulates memcpy
        for i in range(self.size):
            new_data[i] = self.data[i]
        self.data = new_data
        self.capacity = new_capacity
```

* This method is called when we try to add an element to a full array.
* It doubles the current `capacity` of the array.
* A new, larger block of memory (`new_data`) is allocated with the new `new_capacity`.
* The existing elements from the old `self.data` are copied to the `new_data`. This simulates the `memcpy` operation you'd find in lower-level languages.
* Finally, `self.data` is updated to point to this new memory block, and `self.capacity` is updated.

### 🚀 Adding Elements: The `push` Method

The `push` method allows us to add new elements to the end of our array:

```python
    def push(self, value):
        if self.size >= self.capacity:
            self._resize()
        self.data[self.size] = self.element_type(value)
        self.size += 1
```

* It first checks if the array is full (`self.size >= self.capacity`).
* If it's full, it calls the `_resize()` method to increase the capacity.
* Then, it adds the new `value` (converted to the specified `self.element_type`) at the current `self.size` index.
* Finally, it increments `self.size` to reflect the new element.

### 🔍 Accessing Elements: The `get` Method

The `get` method allows us to retrieve an element at a specific index:

```python
    def get(self, index):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        return self.data[index]
```

* It checks if the provided `index` is valid (within the bounds of the current `size`).
* If the index is valid, it returns the element at that `index` from the underlying `self.data`. This direct access is what gives arrays their O(1) time complexity for accessing elements.

### ✍️ Modifying Elements: The `set` Method

The `set` method allows us to change the value of an element at a specific index:

```python
    def set(self, index, value):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        self.data[index] = self.element_type(value)
```

* Similar to `get`, it first validates the `index`.
* If valid, it updates the element at the given `index` with the new `value` (converted to the correct `self.element_type`). This is also an O(1) operation.

### ✂️ Removing Elements: The `remove_at` Method

The `remove_at` method demonstrates how removing an element from the middle of an array can be less efficient:

```python
    def remove_at(self, index):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        for i in range(index, self.size - 1):
            self.data[i] = self.data[i + 1]
        self.data[self.size - 1] = self.element_type()  # Zero-out
        self.size -= 1
```

* It validates the `index`.
* To remove an element at a given `index`, all subsequent elements need to be shifted one position to the left to maintain the contiguous nature of the array. This loop (`for i in range(index, self.size - 1): self.data[i] = self.data[i + 1]`) performs this shifting.
* The last element is then "zeroed out" (set to the default value for the `element_type`).
* Finally, `self.size` is decremented. This shifting operation gives `remove_at` a time complexity of O(n) in the worst case (removing from the beginning).

### 🗑️ Cleaning Up: The `destroy` Method

The `destroy` method simulates freeing the allocated memory:

```python
    def destroy(self):
        # Simulates free — not strictly needed in Python
        self.data = None
        self.size = 0
        self.capacity = 0
```

* In Python, due to automatic garbage collection, explicitly freeing memory isn't always necessary. However, in lower-level languages, this would be crucial to prevent memory leaks. This method sets `self.data` to `None`, effectively releasing the reference to the allocated memory.

### 👁️ Seeing Our Array: The `__repr__` Method

The `__repr__` method provides a user-friendly string representation of our `RawArray` object:

```python
    def __repr__(self):
        items = [self.data[i] for i in range(self.size)]
        return f"RawArray(size={self.size}, capacity={self.capacity}, data={items})"
```

* It creates a list of the actual elements stored in the array.
* It then returns a string that shows the current `size`, `capacity`, and the `data` (the elements).

### 🤔 Why Go Through This?

By building our own simplified array, we gain a much deeper understanding of:

* **Contiguous Memory Allocation:** How arrays rely on storing elements next to each other in memory.
* **Fixed Element Type (in traditional arrays):** The constraint that all elements must be of the same type for consistent memory management.
* **O(1) Access:** The efficiency of accessing elements by index due to direct memory addressing.
* **O(n) Insertion/Deletion (in the middle):** The cost of shifting elements when modifying the array's structure.
* **Dynamic Resizing:** The mechanism by which dynamic arrays grow to accommodate more data, and the trade-offs involved (potential O(n) cost for resizing, but amortized O(1) for appends).

This exercise highlights the fundamental principles behind the arrays we use every day in higher-level languages. Understanding these basics is crucial for making informed decisions about which data structure to use in different scenarios and for optimizing your code.

### 🚀 Next Steps

Now that we've seen a raw implementation of an array, we can better appreciate the convenience and power of built-in list types in languages like Python. In future posts, we'll explore how these fundamental building blocks are used to create more complex and efficient data structures.

Stay curious, and keep building!

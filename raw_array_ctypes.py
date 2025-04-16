from ctypes import *

class RawArray:
    def __init__(self, element_type, initial_capacity=2):
        self.element_type = element_type
        self.capacity = initial_capacity
        self.size = 0
        self.data = (self.element_type * self.capacity)()  # malloc

    def _resize(self):
        print(f"Resizing from {self.capacity} to {self.capacity * 2}")
        new_capacity = self.capacity * 2
        new_data = (self.element_type * new_capacity)()
        # Simulates memcpy
        for i in range(self.size):
            new_data[i] = self.data[i]
        self.data = new_data
        self.capacity = new_capacity

    def push(self, value):
        if self.size >= self.capacity:
            self._resize()
        self.data[self.size] = self.element_type(value)
        self.size += 1

    def get(self, index):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        return self.data[index]

    def set(self, index, value):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        self.data[index] = self.element_type(value)

    def remove_at(self, index):
        if index >= self.size:
            raise IndexError("Index out of bounds")
        for i in range(index, self.size - 1):
            self.data[i] = self.data[i + 1]
        self.data[self.size - 1] = self.element_type()  # Zero-out
        self.size -= 1

    def destroy(self):
        # Simulates free — not strictly needed in Python
        self.data = None
        self.size = 0
        self.capacity = 0

    def __repr__(self):
        items = [self.data[i] for i in range(self.size)]
        return f"RawArray(size={self.size}, capacity={self.capacity}, data={items})"

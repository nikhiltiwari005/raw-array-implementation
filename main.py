if __name__ == "__main__":
    # 🧪 Test with int
    arr = RawArray(c_int)

    arr.push(10)
    arr.push(20)
    arr.push(30)

    print(arr)

    print("Element at 1:", arr.get(1))

    arr.set(1, 99)
    print("After set at 1:", arr)

    arr.remove_at(0)
    print("After remove at 0:", arr)

    arr.push(40)
    arr.push(50)

    print("Final:", arr)

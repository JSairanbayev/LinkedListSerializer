# LinkedListSerializer

Doubly linked list serializer/deserializer written in C++ with binary file I/O.

## Features

- Read list description from text file (data + rand index)
- Build doubly linked list with random pointers
- Serialize list to binary file
- Deserialize from binary file and verify

## How it works

1. Reads `inlet.in` with format `<data>;<rand_index>` per line
2. Builds a doubly linked list (prev/next pointers)
3. Links random pointers by index
4. Writes binary representation to `outlet.out`
5. Reads binary file back and rebuilds the list

## Technologies

- C++
- Pointers and dynamic memory (new/delete)
- Structs with pointer fields
- Doubly linked list (prev, next, rand)
- String parsing (find, substr, stoi)
- Binary file I/O (write/read)

## How to run

1. Clone the repository
2. Open `LinkedListSerializer.cpp` in Visual Studio or any C++ compiler
3. Build and run
4. Program creates `inlet.in` and serializes to `outlet.out`

## Author

**Zheka Sairanbayev** — C++ trainee developer

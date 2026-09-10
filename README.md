# Line

A class that can help you to work with massives in C++.

## Overview

Line is a C++ library that provides a convenient and efficient class for working with arrays (massives). It simplifies common array operations and provides a clean, object-oriented interface for array manipulation and management.

## Features

- ✅ Easy-to-use array class wrapper
- ✅ Dynamic array management
- ✅ Common array operations (insert, delete, search)
- ✅ Array element access and iteration
- ✅ Memory-safe array handling
- ✅ Support for various data types
- ✅ Efficient array manipulation

## Technology Stack

- **Language:** C++ (71.9%)
- **Build Scripts:** Batch files (28.1%)
- **Platform:** Windows/Cross-platform

## Getting Started

### Prerequisites

- C++ compiler (MSVC, GCC, or Clang)
- Standard C++ Library
- Windows (for batch scripts) or compatible build environment

### Installation

1. Clone the repository:
```bash
git clone https://github.com/Yan-519/Line.git
cd Line
```

2. Build the project (Windows):
```bash
build.bat
```

Or compile manually:
```bash
g++ -o line *.cpp
```

3. Include in your project:
```cpp
#include "Line.h"
```

## Usage Example

```cpp
#include "Line.h"

int main() {
    // Create a Line object
    Line<int> myArray;
    
    // Add elements
    myArray.insert(10);
    myArray.insert(20);
    myArray.insert(30);
    
    // Access elements
    std::cout << myArray[0] << std::endl;
    
    // Remove elements
    myArray.remove(1);
    
    return 0;
}
```

## API Reference

### Main Operations

- `insert(value)` - Add an element to the array
- `remove(index)` - Remove an element at the specified index
- `search(value)` - Search for a value in the array
- `size()` - Get the number of elements
- `clear()` - Clear all elements from the array
- `operator[]` - Access elements by index

## Project Structure

```
Line/
├── README.md
├── *.cpp files         (Implementation)
├── *.h files           (Headers)
├── build.bat           (Build script)
└── .gitignore
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available under the MIT License.

## Author

Yan-519

---

For more information or issues, please open an issue on the GitHub repository.

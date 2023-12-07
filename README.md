# crycall | Compile-Time Calls Obfuscator for C++14+

## Description
This repository provides a compile-time calls obfuscator based on lambdas, virtual calls and on how std::function works.\
Users can easily obfuscate their calls using the `crycall` and `crycall_virtual` macro provided in the header.\
The repository includes an example demonstrating the usage of `crycall`.\
`Needs optimization off (C/C++ -> Optimization -> "Optimization" and "Whole Program Optimization")`

## Key Aspects
 - The actual sub that's being called is hidden.
 - All the arguments passed in the call are hidden.
 - Memory is correctly managed, everything gets free'ed after usage.
 - Supports virtual functions (see crycall_virtual macro)
 - Works well with crystr ([see the repo](https://github.com/Android1337/crystr))
 - Supports C++14 and higher versions.

## How it shows
[Look here](https://imgur.com/a/WN23wmS)

## Repository Structure
- **`include/`**: Contains the `crycall.hpp` header file providing the compile-time calls obfuscation mechanism.
- **`src/`**: Holds the example `main.cpp` file showcasing the usage of the `crycall` macro.
- **`LICENSE`**: Licensing information for the provided code.
- **`README.md`**: Documentation explaining how to use the `crycall` macro and example usage.

## Usage
```cpp
crycall(returntype, function, args...)
```
or
```cpp
crycall_virtual(returntype, class_address, virtual_index, args...)
```
Note that the virtual_index must be the index and not the virtual offset. (index = offset / 0x8)

## Usage Example
The repository includes an example demonstrating the usage of the `crycall` macro:

### `main.cpp`
```cpp
#include <iostream>
#include "crycall.hpp"

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    printf("sum: %d", crycall(int, sum, 10, 5));

    return 0;
}
```

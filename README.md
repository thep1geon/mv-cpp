# Introduction
A simple virtual machine and programming language written in C++. Inspired by Tsoding.

[Writing VM for my Lisp in C — Day 1](https://www.youtube.com/watch?v=0irYsCYuZws&list=PLpM-Dvs8t0VY73ytTCQqgvgCWttV3m8LM) 

[Tsoding](https://www.youtube.com/@TsodingDaily)

## Quick Start

Run:
If you want to install the virtual machine on your computer, 
you can run ```make install```.

This will install the executable and place the standard library in
```$HOME/.config/mvi/std```.

Then you can run:

```bash
mvi app.mv
```

Without installing on the system:

```bash
make
bin/mvi app.mv
```
Compile the virtual machine and read the file "app.mv"

## Features
 - [X] Comments
 - [X] labels
 - [X] Dot Operator
 - [X] Memory
 - [X] Strings
 - [X] Built-in functions (e.g., "print_str")
 - [X] Utility instructions (e.g., "size", "swap")
 - [X] Functions
 - [X] Including from other files
 - [X] Call Stack

## Project Goals

The primary goal of this project is to create a functional virtual machine and 
programming language while learning and experimenting with language design, 
virtual machine architecture, and low-level programming concepts.

## Getting Started

Dependencies

- Make
- gcc

1. Clone the repo: ```git clone https://www.github.com/TheP1geon/mv```
2. Compile with the makefile ```make```
3. [Write](#writing-your-own-programs) your own program or use one of the examples
4. Run: ```./bin/mvi <program> [debug]```

## Writing Your Own Programs

1. Make a new file ending in ".mv"
2. Write the program (see the [Docs](https://github.com/TheP1geon/mv-cpp/blob/main/docs.md))
3. Save the file
4. Run the program with the compiled vm

## Examples

```vasm
import "stdstr.mv" # Include the standard library

str "Hello World!" | p # create a new string in memory and set p to the ptr
call print_str p # Pushes p onto the stack before calling print_str
```

Prints "Hello World!" with a newline to the standard output

```
Hello World!
```

## Contributing

Feel free to contribute to the project. Be sure to:

- Clearly describe the changes made
- Test the changes to ensure they don't introduce new issues
- Follow the project's coding style and guidelines

# Documentation

Welcome to the offical documentation of the virtual machine and the programming
language 'Vassembly'

## Table of Contents

- [Introduction](#introduction)
- [Language Basics](#language-basics)
    - [Stack Operations](#stack-operations)
    - [Arithmetic Operations](#arithmetic-operations)
    - [Jumps](#jumps)
    - [Labels & Functions](#labels-&-functions)
    - [Memory Operations](#memory-operations)
    - [Utility Operations](#utility-operations)
    - [Dot and Pipe Operators](#dot-and-pipe-operators)
    - [Other](#other)
- [Standard Library](#standard-library)
- [Virtual Machine](#virtual-machine)
    - [Stack](#stack)
    - [Registers](#registers)
    - [Heap Memory](#heap)
    - [Programs](#programs)
- [Final Notes](#final-notes)

## Introduction

The Vassembly language is the assembly of the virtual machine. Both the virtual
machine and the language are written in C; Therefore the language is also interpreted
in C

## Language Basics

An example program might look something like this:
```vasm
push 19
push 23
add

dump
```

The numbers 19 and 23 are pushed to the stack, added, and then the stack
printed is printed

```
42
```

### Stack Operations

- push [int|str|var|dot op]*: Pushes the argument(s) one by one onto the stack.
                         Each argument can be a number, a string literal,
                         a variable, or a [dot operator](#dot-operator). In the case of a variable, the
                         variable's value is pushed on the stack.

- pop [index|var]: Pops the top of the stack. If an index is provided,
                   the popped value is placed in the register at that
                   index. If a variable is present, a new variable is
                   created and set to the value of the popped element.

- dupe [index]: Duplicates the top of the stack. If an index is present, 
                then the item at that index is duplicated and placed on the 
                top of stack. Where zero is the top of the stack.

- swap: Swaps the top element with the second-to-top element

### Arithmetic Operations

- add: Adds the first two elements on the stack and pushes the result

- sub: Subtracts the top element from the second element and pushes the result

- mult: Multiples the two elements and pushes the result

- div: Divides the top element by the second element and pushes the result

- mod: Divides the top element by the second element and pushes the remainder

- inc: Increments the top of the stack

- dec: Decrements the top of the stack

### Labels & Functions

#### Note:
During the execution of a program when a label is encountered, it is run like normal.
However, when a function is found, it is skipped.

- [label:] : Creates a new label that you can jump to

- func [label:] : Creates a new function, which is just a fancy label

- ret: All functions need to end in ret which returns from the function

- call [label] [var|int]*: Makes a call to the function [label]. If any 
                           values are provided after the call function,
                           they are automatically pushed on to the stack
                           before jumping to the function. You can think of it
                           like passing parameters to a function in C.

### Jumps

#### Note: condition
The condition for a jump can be a number, variable or a [dot operator](#dot-operator)

- jmp [label]: Unconditional jump to [label]

- jmp_gt [label] [condition]: Jumps to [label] if the top of the stack is greater than [condition]

- jmp_gteq [label] [condition]: Jumps to [label] if the top of the stack is greater than or equal to [condition]

- jmp_lt [label] [condition]: Jumps to [label] if the top of the stack is less than [condition]

- jmp_lteq [label] [condition]: Jumps to [label] if the top of the stack is less than or equal to [condition]

- jmp_eq [label] [condition]: Jumps to [label] if the top of the stack is to [condition]

- jmp_neq [label] [condition]: Jumps to [label] if the top of the stack is not to [condition]

### Memory Operations

- read [address: int|dot|var]: The value at the address given is pushed to the stack.
                      This is useful when reading strings or arrays.

- write [address: int|dot|var] [value: int|dot|var]: Sets the value at [address] to [value]

- str ["string"]: Finds a random address in memory and writes the string there.
                  The the pointer to start of the string is pushed to the stack

- arr [size: int|dot|var] [default: int|dot|var]: allocates [size] on the heap and pushes the pointer to the start
                        on to the stack

### Utility Operations

- dump [index]: Prints, as a number, the index in the stack (0 being the top of the stack)

- print [index|var]: Prints, as a character, the index in the stack (0 being the top of the stack)
                     If a variable is provided, its value is printed instead.

- size: Pushes to the top of the stack the size of the stack

- stop: Stops the program right there.

- wait [time(secs)]: Make the program wait for [time] seconds.

### Dot and Pipe Operators

A powerful feature of the assembly is the dot operator and pipe operator.

The dot operator is basically replaced with the top of the stack at runtime.
and its sibling, the double-dot operator is replaced with the second-to-top element
of the stack.

```vasm
push 1 2

# Stack:
# 1
# 2 (top)

set x .  # x is set to 2

set y .. # y is set to 1

print x # 2

print y # 2
```

Another feature is the pipe operator. This one works very similar to the
unix pipe. It takes whatever is on the top of the stack and pops in into a
variable.

```vasm
push 32 | x # Pushes 32 and imediately pops it into x
print x # 32
```

```vasm
import "std.mv"

str "Hello World!" | str_ptr # str usually pushes the ptr to the stack. 
                             # Instead we popped it into str_ptr

call print_str str_ptr
```

### Other

- input ["str"] [default: int]: Gets a number from the user and pushes it onto
                                the stack. If a "str" is present it is used as
                                a prompt and a default if the operation failed.

- set [variable name] [val: int|var|dot]: Create a new variable and sets it to [val]

- del [var]: Deletes [var] from the var map.

- import ["file path"]: Adds another program to your file. No code from the
                        the imported program is run since everything is
                        inserted to the top of the program.

#### Note
These operators are related to the Virtual Machine's registers [Registers](#registers)

- mov [index: int|var|dot]: If only a register [index] is provided, the value at that register is pushed to the stack

- mov [index: int|var|dot] [value: int|var|dot]: [value] is placed in register [index]

## Standard Library

The standard library is a collection of useful functions such as printing
strings, better math operations, clearing the stack, etc.

It is made up of two files at the moment, "math.mv" and "std.mv"

## Virtual Machine

The virtual machine is [Stack](#stack) based

### Stack

I programmed the stack from stratch using vanilla C. It's got some operators 
listed here: [Stack Operations](#stack-operations)

### Registers

The machine has 10 registers, this is subject to change, that the language can 
interact with and use. The registers is just an array of numbers

### Heap

The machine also has a much larger array of numbers for the heap memory. I'll 
be completely honest, I don't know if heap is the right term. The language can
also interact with the heap using the [Memory Operations](#memory-operations)

### Programs

The program struct is just an array of Inst's (another struct), it's size and 
the file that the program came from 

# Final Notes

This is the first time I've ever something this big. I only just started learning
how to code last year. I did this to learn more about computers and how they 
work.

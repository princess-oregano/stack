# stack

Implementation of protected stack.

## Table of contents
* [Prerequisites](#prerequisites)
* [Installation and setup](#installation-and-setup)
* [Info](#info)

## Prerequisites
* `git`
* `make`
* `g++`

Program was built and tested on Linux 6.1.21-1-MANJARO.

## Installation and setup
1. Download all source files into one folder:
```
$ git clone https://github.com/princess-oregano/stack
```
2. Open the subfolder with source files and build with Make:
```
$ cd stack/
$ make
```
A little test program will start: it will prompt you to enter some integer
numbers until first non-int. Then it will call `stack_dump()`, and pop integers,
printing each number in formar `ret = <number>`. If installation is successful,
no error will emerge.
2. To use stack in your programms, import all files, except `main.cpp`, to one
folder and include `stack.h` to the files, where you want to use the library.
4. To remove all object files type this:
```
$ make clean
```
5. To remove all files built by `make` type this:
```
make distclean
```

## Info

* This implementation has two main ways of protection: canaries and hash. Both can
be turned off/on in `config.h` by removing line `#define <HASH/CANARY>`.

* Stack can work with different types of data (int by default). To change it, 
edit line 
```
typedef <type> elem_t;
```
* Used hash function - crc8.


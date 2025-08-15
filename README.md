# Dynamic library template
## Intro
This repo contain a sample for compiling c code without linking. Then link and compile with a simple program.
The function in mylib take a char pointer and print the string start from that char pointer.
Main program call the function with a static string.
## Usage
1. Clone the repo:'git clone https://github.com/NguyenNguyen12/HelloWorldNative.git'
2. Compile (without link) mylib.c: `gcc -c mylib.c`
3. Compile myprog.c: `gcc myprog.c mylib.o`
4. Run: `./a.out`
> other C compiler should work
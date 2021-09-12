# Br4in\[fuck\]
This is my shot at a brainfuck interpreter. It's overengineered on purpose.

# How to compile & run
After compiling, you should find the executable in `projectdir/bin/release/`.
For more information, just run `path/to/br4in -h` (TODO: add a help command line option)

## Linux
You just have to run the following in the project directory
```sh
./premake5 gmake
make config=release
```
and it should work just fine.

## Windows
I have not tested it on windows so far, but with a few tweaks it should work there too.
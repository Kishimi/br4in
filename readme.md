# Br4in\[fuck\]
[![C/C++ CI](https://github.com/Kishimi/br4in/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Kishimi/br4in/actions/workflows/c-cpp.yml)
[![CodeQL](https://github.com/Kishimi/br4in/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/Kishimi/br4in/actions/workflows/codeql-analysis.yml)

This is my shot at a brainfuck interpreter. It's overengineered on purpose.

# How to compile & run
After compiling, you should find the executable in `projectdir/bin/release/`.
For more information, just run `path/to/br4in -h`

## Linux
You just have to run the following in the project directory
```sh
./premake5 gmake
make config=release
```
and it should work just fine.

## Windows
I have not tested it on windows so far, but with a few tweaks it should work there too.

# C++ networking

## Environment

OS: Windows 10 \
Editor: VSCode (with [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)) \
Compiler: g++.exe ([x86_64-posix-seh-rev0, Built by MinGW-W64 project](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)) 8.1.0

Some of the functions does not work properly with this environment. For example, %F, %T, %z in strftime doesn't work by default, and -lucrtbase flag has to be added. Due to this issue, compiling environment might be changed in the future.

## References

[Winsock2.h reference](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/)

[C++ Network Programming Part 1: Sockets](https://www.youtube.com/watch?v=gntyAFoZp-E) \
[C++ Network Programming Part 2: TCP & UDP](https://www.youtube.com/watch?v=sXW_sNGvqcU)

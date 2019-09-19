*** WARNING: DO NOT TRY TOO HARD TO BUILD THE ORIGINAL EXECUTABLE! ***

Please remember that any little difference, not matter how small it is,
can lead to a vastly different EXE layout. This includes differences in:

- The development tools (or parts of such); For instance, a compiler, a linker,
an assembler, or even a support library or header. A version number is not
a promise for having the exact tool used to reproduce some executable.
- The order in which source code files are listed in a given project file.
- Project settings.
- Source file specific settings in such a project.
- The order in which source code files are passed to a linker.
- Any modification to a source code file (especially a header file).
- More than any of the above.

Following the warning, a description of the way in which the executable was
reproduced is given.

This codebase is based on the Catacomb Abyss sources as originally released by
Richard Mandel from Flat Rock Software on 2014. While this release includes
a few data files like ABSADICT.OBJ, other versions were extracted from an
original EXE as required.

With Borland C++ 2.0, this patched codebase can be used to reproduce the
executable for The Catacomb Abyss Shareware 1.13 (QA [0]).

Borland C++ 2.0 for DOS should be used for these builds; Not Borland C++ 3.1
nor any version of Turbo C/C++, but precisely Borland C++ 2.0.
After opening the project with BC20, chances are you will need to set up
the correct LIB and INCLUDE paths in the project. Either way, you should
then be able to build the corresponding executable.

With the help of LZEXE 0.91, you can get precisely the original 
Shareware 1.13 executable, byte-by-byte.

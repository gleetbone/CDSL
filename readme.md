# C Data Structure Library

### Overview

This project is a library of data structures and related utilities written in C. In the past I have looked for such a library but couldn't find one that met my needs - either this one was lacking a data structure I needed, that one didn't use a license I could support, or the other one used some kind of language preprocessing that made my source code look like something other than C. So I decided to write this collection, the C Data Structure Library (CDSL), to suit my own requirements:

- written in C for use in C
- consistent style across multiple kinds of data abstractions
- contains all (or nearly all) of the basic data structures
- usable in multithreaded systems
- permissive (MIT-style) license
- fully available source code and lots of test and example code
- easy to use (well, as easy as possible - this is C after all)
- well tested (100% coverage and no valgrind issues)
- primarily intended for use in Linux and Unix-like systems (although most data structures are also usable in non-multithreaded Windows applications)

### Quick Start

If you're like me, you may want to just get to the code and start working. Begin with singly linked lists - look at the SList and Test/SList_test/src directories and see how int_SList.c and int_SList.h are constructed. See how the SList data structure is used in the test files. Come back to this readme file when you're ready for more information.

### License

The software is licensed under the OSI-approved Eiffel Forum License, Version 2. The license text is included at the start of each file. Read it for yourself for the details, but in my understanding this license only requires you to keep the copyright and license information intact. It also requests that you publicly release improvements (additions, bug reports, bug fixes, etc.) but does not require you to do so. You can otherwise use and/or modify it as you see fit to meet your needs.

### C Style Object Oriented Programming

The style of programming for this library uses what are sometimes called opaque types. This means that the details of the data structure definitions are hidden from the user of the library, and the only access to the data structures is through the data structure's function API. This may be a bit frustrating for some programmers to get used to, but opaque typing provides encapsulation, one of the three main tenets of object-oriented programming. One of the other object-oriented principles is polymorphism which is provided through *protocols*, discussed later. The third object-oriented principle is inheritance. The C language has no built-in support for inheritance, and this library, at least this version of this library, does not use inheritance. Not to worry, though, as just using encapsulation provides a very workable basis for data structure design.

### Basic Types

To offer better cross-platform support (different CPU, different compiler, different Operating System), all basic types (signed and unsigned integers, floating point numbers, characters) are assigned names in the include file `base.h`. The name of the type indicates the size of the type in bits (e.g. `int32_t` for a 32 bit signed integer). The character type `char_t` is signed or unsigned as the underlying system defines it. There are separate eight bit signed and unsigned integer types (`int8_t` and `uint8_t`). Complex numbers have either 32 bit float real and imaginary parts (`complex64_t`) or 64 bit double real and imaginary parts (`complex128_t`). Note that using complex numbers requires a C99 or later C compiler.

### Multithreading

All data structures may be made multithreading ready by a macro setting in `base.h`. This adds a mutex feature into each instance of the data structure and locks the data structure during the execution of all of its function API calls. Of course the subject of multithreading is a large one, and while it is true that merely providing a lock for API calls does not magically make an application multithreaded, this kind of locking is usually a prerequisite for doing so.

### Garbage Collection

Deleting data that is no longer needed or used in an application is a necessity for large or long-running applications, and the CDSL provides API calls to delete or "dispose" of data structures. Since many of the data structures contain other data structures (like a list of strings), there are usually two dispose functions provided - a `dispose` and a `deep_dispose`. The former deletes the container data structure itself but does not delete the contained data structures (disposing of a list containing strings deletes the list but does not delete the strings it contains - presumably you would have a separate way to access the strings). The latter deletes both the container data structure and the contained data structure (so calling deep_dispose on a list of strings deletes both the list and the strings). Both methods of disposal will eventually be required in most larger applications. The CDSL unit test routines have been successfully run against Valgrind and provide examples of properly disposing of all allocated memory. The data structures in CDSL also work well with the Boehm automatic garbage collector. To use this automated collector, you need to enable the macro GC_ENABLED in `base.h` and include the library `gc` for linking.

### Specializing Container Classes

Many of the data structures in the library are containers that may hold any other type of data structure, whether basic types or pointers to user-defined structures. The same code is used to support all of the possible variants. To specialize a container data structure, one has to define certain macros in separate \*.c and \*.h files that define the specialized data structure. For example, to generate a singly linked list of signed 32 bit integers, one has to create both a C \*.c source file (that will include the `SList.c` file) and a C \*.h header file (that will include the `SList.h` file). Examples are found in the unit test code for the SList data type. Here the source file is named `int_SList.c` and the header file is named `int_SList.h`:

~~~C
// int_SList.c

#include "int_SList.h"

#define VALUE_DISPOSE_FUNCTION( arg )
#define VALUE_DUPLICATE_FUNCTION( arg ) ( arg )

#define Prefix int
#define Type int32_t
#define Type_Code int32_type_code

#include "SList.c"

#undef Prefix
#undef Type
#undef Type_Code
~~~

In the C source file, two function-like macros are defined - one to provide a means to dispose of the contained data type, and the other to provide a means to duplicate the contained data type. Since the contained data type is an integer, no action is required to "delete" the contained type, and the duplicate action is simply to copy the integer's value. Note that the file `SList.c` is itself included into the file `int_SList.c`. Macros are used to define the prefix for this contained type (`int` for integer), to define the contained type (`int32_t` for a signed 32 bit integer), and to define a code for the type (`int32_type_code`) used for internal type checking. 

~~~C
// int_SList.h

#include "base.h"

#define Prefix int
#define Type int32_t

#include "SList.h"

#undef Prefix
#undef Type

~~~

In the C header file, macros are used to define the contained type prefix and type as in the C source file. Note that the macros are undefined at the end of the header file as there may be additonal specialized SList types used.

This use of macros allows the same code in `SList.c` and `SList.h` to be re-used for all potential contained data structures. The contained data structure is either a basic type (integer, float, character) or a pointer to a user-defined data structure. Additionally, the C compiler will provide a warning if an incorrect data structure pointer type is passed as a function parameter to a data structure API function. Internal data structure checks, if enabled, provide more stringent checking of types at runtime.

Also note that the file SList.c and all of the other container data structure \*.c files will **not** compile by themselves. They require inclusion into separate \*.c and \*.h specialization files like the int_SList.c and int_SList.h files.

### Design By Contract 

Design by contract (DbC) is a programming technique originated by Bertrand Meyer in the Eiffel programming language that provides a means of checking and validating properties of software at runtime. The basic approach is to view the interaction of separate software entities as a "contract" or agreed-upon set of conditions that must be true for the interaction to be valid. As a quick example, one of the simplest kinds of contract is that a function parameter that is a pointer to a structure that is to be used in the function must not be void. If the parameter were void, the called function could not perform its action correctly. So the "contract" between the calling function to provide a valid function parameter and the called function which expects a valid function parameter would fail if the pointer were void. A contract failure is a **bug** which needs to be corrected. Generally speaking, a contract failure is not an exception to be handled nor a condition to watched for and taken into account, it is a **bug** in the software. There are four main kinds of contracts used in the CDSL: preconditions, postconditions, invariants, and checks. 

A precondition is, like the void pointer function argument example above, an agreement of what a calling function has to provide to a called function. Common preconditions are usually validity checks on passed function parameters. The calling function is responsible for providing correct parameters, and the called function checks the passed parameters for validity. Besides checking for void pointers, other kinds of preconditions could be checking that indices of arrays are in bounds, or that impossible inputs are not present (such as a negative number input parameter to a square root function). A precondition failure indicates a **bug**, specifically a **bug** in the calling function

Invariants check the internal consistency of the state of a data structure. An example would be that the count of characters in a string (if stored separately in the data structure) is the same as the result of calling `strlen()` on the data structure's character string. If the two counts do not match, then the internal state of the data structure is in error. Again, this indicates a **bug** somewhere in the data structure code. Invariants are checked just before and after a data structure API call is performed. 

Postconditions check that the result of a function is correct. The CDSL code does not contain a lot of postconditions, as similar checking is done in the unit test code. A common example of a postcondition would be that a character that is to be appended to the end of a string actually exists at the end of the string at the completion of the function. Obviously if the character is not at the expected place, then there is a **bug** somewhere within that API function code. 

Checks are just that, checks on one or more variables in the middle of a function. This version of CDSL has check statements for every memory allocation, ensuring that the allocation produced a valid result. In this case, the failure of a check contract indicates an error related to a shortage of system resources (memory) and not a bug.

Checking contracts at runtime isn't free. Computing them does of course take CPU time and occupy code space. CDSL implements contracts with the `assert()` macro. But in the file `base.h` are other macros that define whether or not a class of contracts is to be included and executed. The contracts themselves are implemented as macros in the file `dbc.h`. It is possible to enable or disable preconditions, invariants, postconditions, and/or checks in the entire system, in a particular data structure, or even for a single data structure API call. If a contract is disabled, the C compiler will see the contract macro as dead code and remove it. A disabled contract macro does not result in unused data or code being added to the application executable.

In the development of CDSL, contracts played a vital role in identifying coding errors and validating correct operation along with unit tests. For you, the user of CDSL, the main contract you should consider enabling during development is the precondition. Invariants, postconditions, and checks should be without error since they deal with the internal workings of the data structure API functions. A CDSL precondition failure you find in the execution of your code indicates a **bug** in your code.

### Coding Style

I follow my own preferences in coding style. I prefer to see the following:

- braces that line up vertically
- use of the dereference operator (*) instead of the arrow (->) for structure element access
- use of additional vertical space for visual separation and clarity 
- spaces instead of tabs, with one indentation level as three spaces
- words in identifiers separated by the underscore (_), not camelCase 

Beyond this simple formatting, there are other higher level conventions used in the CDSL that make function names easier to find and learn. 

#### Data Structure Creation

When creating a new data structure, the creation function will contain the word "make". If several different creation functions are provided, they each will contain the word "make" followed by additional words that further describe the function.

#### Data Structure Deletion 

Functions to delete a data structure contain the word "dispose" or the words "deep_dispose".

#### Data Structure Basic Operations

Most container classes in the CDSL implement the following functions: copy, deep_copy, clone, deep_clone, is_equal, and is_deep_equal. The regular copy, clone, is_equal, and dispose functions operate on the container structure itself. Their deep variants operate on both the container structure and the data contents held in the container. For example, a clone of a singly linked list of strings would produce another singly linked list of strings where the contained strings were the same strings as in the original, whereas a deep_clone would produce a sngly linked list of strings where each contained string was itself a clone of its corresponding string in the original.

#### Container Data Structure Cursors

Many data structure containers allow for iteration through the contained element data. An additional opaque auxiliary data structure called a cursor is used to navigate through this iteration. The container data structure contains a default cursor, and most containers allow for the creation of additonal cursors. API functions to use a cursor usually include the following:

start - make the cursor's current item the first one in the container
forth - move the cursor forward one element
item_at - return the value of the contained data structure at the cursor's location
off - returns 1 if the cursor has passed the last element in the container
is_first - returns 1 if the cursor is at the first element in the container
is_last - returns 1 if the cursor is at the last element in the container
back - (if present) move the cursor backwards one element
finish - (if present) move the cursor to the last element in the container
go( index ) - move the cursor to the element at the index position in the container
remove_at - remove the element at the current cursor position
remove_at_and_dispose - remove and delete the element at the current cursor position

There are other additional common API function names:

count - returns the number of elements in the container
is_empty - returns 1 if the container has no elements present
item( index) - returns the element at the index position in the container
put( value ) - add the value as a new element in the container
remove( value ) - remove the value as an element of the container

#### Command-Query Separation

A design principle for data structure API function calls is that functions that return a value do not alter the state of the data structure (a query). API functions that do not return a value (called procedures in some other programming languages) do alter the state of the data structure (a command). This may not be what one expects - two function calls (one to alter the data structure's state and one to retrieve a value) may be required instead of calling a single operation to do both actions simultaneously.

### Summary of Supported Data Structures

#### Container Data Structures

- list - arrayed list [AList](documentation/AList.md), singly linked list [SList](documentation/SList.md), doubly linked list [DList](documentation/DList.md)
- tree - binary search trees [BSTree](documentation/BSTree.md), red-black binary search trees [RBTree](documentation/RBTree.md), AVL binary search trees [AVLTree](documentation/AVLTree.md), b-trees [BTree_kv](documentation/BTree_kv.md), tries [Trie](documentation/Trie.md)
- hash set [HSet](documentation/HSet.md)
- hash table [HTable](documentation/HTable.md)
- sequence ( resizable array) [Sequence](documentation/Sequence.md)

#### Queues and Stacks

- circular array [Circular_Array](documentation/Circular_Array.md)
- circular buffer [Circular_Buffer](documentation/Circular_Buffer.md)
- deque [Deque](documentation/Deque.md)
- heap [Heap](documentation/Heap.md)
- priority queue [PQueue](documentation/PQueue.md)
- queue [Queue](documentation/Queue.md)
- stack [Stack](documentation/Stack.md)

#### Character Strings

- string - holds a character string, provides a lot of functions to manipulate them [String](documentation/String.md)
- string_utf8 - holds a Unicode UTF8 character string, provides a lot of functions to manipulate them [String_utf8](documentation/String_utf8.md)
- cable - holds very long character strings, provides a lot of functions to manipulate them [Cable](documentation/Cable.md)
- cable_utf8 - holds very long Unicode UTF8 character strings, provides a lot of functions to manipulate them [Cable_utf8](documentation/Cable_utf8.md)

#### Graphs 

- directed graph with edges and vertices [DGraph](documentation/DGraph.md)
- undirected graph with edges and vertices [UGraph](documentation/UGraph.md)

#### Sorters

- bubble sorter [BSorter](documentation/BSorter.md)
- heap sorter [HSorter](documentation/HSorter.md)
- insert sorter [ISorter](documentation/ISorter.md)
- merge sorter [MSorter](documentation/MSorter.md)
- quick sorter [QSorter](documentation/QSorter.md)
- selection sorter [SelSorter](documentation/SelSorter.md)
- shell sorter [SSorter](documentation/SSorter.md)

#### Searchers

- linear searcher [LSearcher](documentation/LSearcher.md)
- binary searcher [BSearcher](documentation/BSearcher.md)

#### Matrices and Vectors

- matrix and vector [Matvec](documentation/Matvec.md)
- fast fourrier transform [Fft](documentation/Fft.md)
- singular value decomposition [Svd](documentation/Svd.md)
- pseudo random number generator: version of ISAAC, a cryptologically secure RNG by Bob Jenkin [Rng_Isaac](documentation/Rng_Isaac.md)
- quaternion [Quaternion](documentation/Quaternion.md)

#### Utility

- agent - holds a function along with its input parameters and result that can be called sometime in the future, similar to what are called continuations in other programming languages [Agent](documentation/Agent.md)
- command line handler - has utilites for parsing and manipulating command line commands and options [Command_Line_Handler](documentation/Command_Line_Handler.md)
- configuration - holds key-value pairs [Configuration](documentation/Configuration.md)
- date time - implements data structures for manipulating date and time [Date_Time](documentation/Date_Time.md)
- temporenc - implements temporenc data structure for manipulating date and time [Temporenc](documentation/Temporenc.md)
- binary file - reads and writes binary files (linux and unix-like OS only) [Binary_File](documentation/Binary_File.md)
- directory - create, delete, list directories (linux and unix-like OS only) [Directory](documentation/Directory.md)
- input file reader - reads lines from text file, parses into tokens (linux and unix-like OS only) [Input_File_Reader](documentation/Input_File_Reader.md)
- raw buffer - reads and writes basic types of different sizes and endianness to and from a byte array [Raw_Buffer](documentation/Raw_Buffer.md)
- tuple - user defined data structure configured at run time that can hold fields for integers, floating point numbers, strings, and pointers [Tuple](documentation/Tuple.md)

### Protocols

An auxiliary and optional design feature of the data structures is the use of protocols to achieve polymorphism. Polymorphism means "many shapes", and in software refers to the capability of a data structure to be used as different kinds of things at the same time. In most object oriented programming languages this goes hand in hand with inheritance - for example, if the classes `Circle` and `Square` both inherit from the class `Shape`, then `Circle`s and `Square`s can also be used as `Shape`s. Since there is no easy implementation of inheritance in C, we achieve polymorphism in a different way - by implementing an additional bit of code that we will call a protocol. A protocol is similar to an interface in Java or a pure virtual base class in C++ in that it specifies a set of API functions that a class implements. In C we add a couple of data fields and some code to each data structure to permit protocol interfaces to be invoked on that data structure. 

For the container data structures like lists, trees, hash sets, hash tables, and sequences, there are a few common protocols that are supported by multiple data structures - such as iteration and indexing. The iteration protocol P_Iterable supports API functions to iterate through the items in a container data structure with functions described in the earlier section on cursors like start, forth, item, off, and is_empty. This protocol is supported by lists, trees, hash sets, and hash tables but not sequences. Another common protocol is P_Indexable which supports API functions like count and item( index ). This protocol is supported by lists and sequences but not by trees, hash sets, or hash tables.

Using the P_Iterable protocol allows one to iterate through the items in a container data structure without having to know which type of container data structure is involved - one just calls the API functions of the protocol. Use of protocols is certainly not required for most applications, but occasionally it comes in handy for certain kinds of programming tasks. Examples of protocol use are available for each data structure type that supports them in their unit test directory. To enable protocols, define the macro `PROTOCOLS_ENABLED` in `base.h`.

### Testing

Testing of the data structures and utilities in the CDSL is done using the cunit framework. Cunit is used to run a test suite, requiring only that test functions of the test suite be registered with cunit. Each data structure has its own test suite that can be found in the `Test` subdirectory.

To build a test, go to the test directory for the class of interest in the terminal and type "./b". The test projects are configured to use the premake build utility with relative paths to all the other necessary source files. Of course, your project does not have to use this utility.

Some short bash command files are supplied for each test directory:

- `./a` automatically reformat the CDSL source files using the astyle utility
- `./m` re-run the premake utility (to initialize a new test directory, incorporate a new source file, or accomodate a change in the premake4.lua configuration file)
- `./bc` delete all object files
- `./b` compile and link the test project
- `./d` generate a stack trace from a core dump
- `./g` generate a code coverage file using gcov - the generated file will be in the build subdirectory
- `./v` run the test program with valgrind

### Enhancements from CDSL Version 1

CDSL is now fundamentally complete. Changes and additions from Version 1 are the following:

- All data structures are tested with 100% gcov coverage and no valgrind issues
- no known bugs
- dispose_with_contents() functions replaced with deep_dispose() functions
- dispose functions take a doubly dereferenced pointer as an input parameter so that the dispose functions can set the original pointer to the data structure to NULL upon its disposal
- now includes UTF-8 Unicode character string and cable data structures
- now contains B-Trees and Tries
- Experimental support for Windows - see macro definitions in 'base/base.h'

Greg Lee
October 30, 2024


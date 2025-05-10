# Q++

A C++ library to operate rational numbers and vectors and matrices with rational entries; and to create and validate vector spaces as classes.


## Requirements

- C++'s standard must be C++17 or older (due to the use of Google Test). You can check the standard your compiler uses by printing the macro `__cplusplus` in a C++ file, and then mapping the output to the standard using [this StackOverflow article](https://stackoverflow.com/questions/2324658/how-to-determine-the-version-of-the-c-standard-used-by-the-compiler) or the [GCC documentation](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html).


## Building the project

To build the project in the folder of your preference (I believe it works in Linux and Windows, BUT REQUIRES CONFIRMATION), execute the following commands:

```bash
mkdir build
cd build
cmake ../
cmake --build .
```

Now, if you want to run the tests, you may do so by executing `ctest` or 

```bash
cd root_directory/
ctest -R tests/{your_test_program_name}.cpp
```

if you want to run a specific test. Additionally, you can run any of the executables declared in the [CMake configuration file](CMakeLists.txt) by changing to the `build/` directory and running any of the executables (`./{executable name}` if in Linux or `{executable_name}.exe` if in Windows):

```bash
#In Linux
cd build/
./{executable_name}
```

>**Important**: To make the building process more efficient, if you modified source files (in the `utils/` directory or the root directory) or test files (in the `tests/` directory), you can run `make` to update the executables any of the modified files could be related to, as long as new dependencies haven't been added.

## Helpful links

- Cmake documentation: https://cmake.org/cmake/help/latest/guide/tutorial/index.html
- Google test documentation: https://google.github.io/googletest/
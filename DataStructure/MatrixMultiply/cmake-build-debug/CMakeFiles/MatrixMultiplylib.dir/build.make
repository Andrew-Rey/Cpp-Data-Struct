# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\xrCLang\CLion\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\xrCLang\CLion\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MatrixMultiplylib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MatrixMultiplylib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MatrixMultiplylib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MatrixMultiplylib.dir/flags.make

CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/flags.make
CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/includes_CXX.rsp
CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj: ../src/Matrix.cpp
CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj -MF CMakeFiles\MatrixMultiplylib.dir\src\Matrix.cpp.obj.d -o CMakeFiles\MatrixMultiplylib.dir\src\Matrix.cpp.obj -c D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\Matrix.cpp

CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.i"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\Matrix.cpp > CMakeFiles\MatrixMultiplylib.dir\src\Matrix.cpp.i

CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.s"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\Matrix.cpp -o CMakeFiles\MatrixMultiplylib.dir\src\Matrix.cpp.s

CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/flags.make
CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/includes_CXX.rsp
CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj: ../src/MatrixIO.cpp
CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj -MF CMakeFiles\MatrixMultiplylib.dir\src\MatrixIO.cpp.obj.d -o CMakeFiles\MatrixMultiplylib.dir\src\MatrixIO.cpp.obj -c D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixIO.cpp

CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.i"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixIO.cpp > CMakeFiles\MatrixMultiplylib.dir\src\MatrixIO.cpp.i

CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.s"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixIO.cpp -o CMakeFiles\MatrixMultiplylib.dir\src\MatrixIO.cpp.s

CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/flags.make
CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/includes_CXX.rsp
CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj: ../src/MatrixMultiplier.cpp
CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj: CMakeFiles/MatrixMultiplylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj -MF CMakeFiles\MatrixMultiplylib.dir\src\MatrixMultiplier.cpp.obj.d -o CMakeFiles\MatrixMultiplylib.dir\src\MatrixMultiplier.cpp.obj -c D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixMultiplier.cpp

CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.i"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixMultiplier.cpp > CMakeFiles\MatrixMultiplylib.dir\src\MatrixMultiplier.cpp.i

CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.s"
	"D:\xrCLang\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\src\MatrixMultiplier.cpp -o CMakeFiles\MatrixMultiplylib.dir\src\MatrixMultiplier.cpp.s

# Object files for target MatrixMultiplylib
MatrixMultiplylib_OBJECTS = \
"CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj" \
"CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj" \
"CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj"

# External object files for target MatrixMultiplylib
MatrixMultiplylib_EXTERNAL_OBJECTS =

libMatrixMultiplylib.a: CMakeFiles/MatrixMultiplylib.dir/src/Matrix.cpp.obj
libMatrixMultiplylib.a: CMakeFiles/MatrixMultiplylib.dir/src/MatrixIO.cpp.obj
libMatrixMultiplylib.a: CMakeFiles/MatrixMultiplylib.dir/src/MatrixMultiplier.cpp.obj
libMatrixMultiplylib.a: CMakeFiles/MatrixMultiplylib.dir/build.make
libMatrixMultiplylib.a: CMakeFiles/MatrixMultiplylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libMatrixMultiplylib.a"
	$(CMAKE_COMMAND) -P CMakeFiles\MatrixMultiplylib.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MatrixMultiplylib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MatrixMultiplylib.dir/build: libMatrixMultiplylib.a
.PHONY : CMakeFiles/MatrixMultiplylib.dir/build

CMakeFiles/MatrixMultiplylib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MatrixMultiplylib.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MatrixMultiplylib.dir/clean

CMakeFiles/MatrixMultiplylib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug D:\xrCLang\Cpp-Data-Struct\DataStructure\MatrixMultiply\cmake-build-debug\CMakeFiles\MatrixMultiplylib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MatrixMultiplylib.dir/depend


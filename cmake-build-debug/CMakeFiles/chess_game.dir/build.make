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
CMAKE_COMMAND = "D:\JetBrains\CLion\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\JetBrains\CLion\CLion 2022.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\chess_game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\chess_game\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/chess_game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chess_game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chess_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess_game.dir/flags.make

CMakeFiles/chess_game.dir/main.cpp.obj: CMakeFiles/chess_game.dir/flags.make
CMakeFiles/chess_game.dir/main.cpp.obj: ../main.cpp
CMakeFiles/chess_game.dir/main.cpp.obj: CMakeFiles/chess_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\chess_game\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess_game.dir/main.cpp.obj"
	"D:\JetBrains\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_game.dir/main.cpp.obj -MF CMakeFiles\chess_game.dir\main.cpp.obj.d -o CMakeFiles\chess_game.dir\main.cpp.obj -c D:\chess_game\main.cpp

CMakeFiles/chess_game.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess_game.dir/main.cpp.i"
	"D:\JetBrains\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\chess_game\main.cpp > CMakeFiles\chess_game.dir\main.cpp.i

CMakeFiles/chess_game.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess_game.dir/main.cpp.s"
	"D:\JetBrains\CLion\CLion 2022.2.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\chess_game\main.cpp -o CMakeFiles\chess_game.dir\main.cpp.s

# Object files for target chess_game
chess_game_OBJECTS = \
"CMakeFiles/chess_game.dir/main.cpp.obj"

# External object files for target chess_game
chess_game_EXTERNAL_OBJECTS =

chess_game.exe: CMakeFiles/chess_game.dir/main.cpp.obj
chess_game.exe: CMakeFiles/chess_game.dir/build.make
chess_game.exe: CMakeFiles/chess_game.dir/linklibs.rsp
chess_game.exe: CMakeFiles/chess_game.dir/objects1.rsp
chess_game.exe: CMakeFiles/chess_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\chess_game\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable chess_game.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\chess_game.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess_game.dir/build: chess_game.exe
.PHONY : CMakeFiles/chess_game.dir/build

CMakeFiles/chess_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\chess_game.dir\cmake_clean.cmake
.PHONY : CMakeFiles/chess_game.dir/clean

CMakeFiles/chess_game.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\chess_game D:\chess_game D:\chess_game\cmake-build-debug D:\chess_game\cmake-build-debug D:\chess_game\cmake-build-debug\CMakeFiles\chess_game.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chess_game.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lab11.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab11.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab11.dir/flags.make

CMakeFiles/Lab11.dir/main.cpp.o: CMakeFiles/Lab11.dir/flags.make
CMakeFiles/Lab11.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab11.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab11.dir/main.cpp.o -c "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/main.cpp"

CMakeFiles/Lab11.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab11.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/main.cpp" > CMakeFiles/Lab11.dir/main.cpp.i

CMakeFiles/Lab11.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab11.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/main.cpp" -o CMakeFiles/Lab11.dir/main.cpp.s

# Object files for target Lab11
Lab11_OBJECTS = \
"CMakeFiles/Lab11.dir/main.cpp.o"

# External object files for target Lab11
Lab11_EXTERNAL_OBJECTS =

Lab11: CMakeFiles/Lab11.dir/main.cpp.o
Lab11: CMakeFiles/Lab11.dir/build.make
Lab11: CMakeFiles/Lab11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab11"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab11.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab11.dir/build: Lab11

.PHONY : CMakeFiles/Lab11.dir/build

CMakeFiles/Lab11.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab11.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab11.dir/clean

CMakeFiles/Lab11.dir/depend:
	cd "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11" "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11" "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug" "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug" "/macOS/учеба/KAI/2 курс/САОД/Лабы SAOD/Lab11/cmake-build-debug/CMakeFiles/Lab11.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab11.dir/depend


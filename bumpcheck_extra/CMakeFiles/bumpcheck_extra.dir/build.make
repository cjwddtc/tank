# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.4

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\code_package\cmake\bin\cmake.exe

# The command to remove a file.
RM = E:\code_package\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\code\bumptest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\code\bumptest

# Include any dependencies generated for this target.
include bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/depend.make

# Include the progress variables for this target.
include bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/progress.make

# Include the compile flags for this target's objects.
include bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/flags.make

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/flags.make
bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/includes_CXX.rsp
bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj: bumpcheck_extra/square.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj"
	cd /d E:\code\bumptest\bumpcheck_extra && E:\code_package\gcc\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bumpcheck_extra.dir\square.cpp.obj -c E:\code\bumptest\bumpcheck_extra\square.cpp

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bumpcheck_extra.dir/square.cpp.i"
	cd /d E:\code\bumptest\bumpcheck_extra && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\code\bumptest\bumpcheck_extra\square.cpp > CMakeFiles\bumpcheck_extra.dir\square.cpp.i

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bumpcheck_extra.dir/square.cpp.s"
	cd /d E:\code\bumptest\bumpcheck_extra && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\code\bumptest\bumpcheck_extra\square.cpp -o CMakeFiles\bumpcheck_extra.dir\square.cpp.s

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.requires:

.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.requires

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.provides: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.requires
	$(MAKE) -f bumpcheck_extra\CMakeFiles\bumpcheck_extra.dir\build.make bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.provides.build
.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.provides

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.provides.build: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj


# Object files for target bumpcheck_extra
bumpcheck_extra_OBJECTS = \
"CMakeFiles/bumpcheck_extra.dir/square.cpp.obj"

# External object files for target bumpcheck_extra
bumpcheck_extra_EXTERNAL_OBJECTS =

lib/libbumpcheck_extra.a: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj
lib/libbumpcheck_extra.a: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/build.make
lib/libbumpcheck_extra.a: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\lib\libbumpcheck_extra.a"
	cd /d E:\code\bumptest\bumpcheck_extra && $(CMAKE_COMMAND) -P CMakeFiles\bumpcheck_extra.dir\cmake_clean_target.cmake
	cd /d E:\code\bumptest\bumpcheck_extra && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bumpcheck_extra.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/build: lib/libbumpcheck_extra.a

.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/build

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/requires: bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/square.cpp.obj.requires

.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/requires

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/clean:
	cd /d E:\code\bumptest\bumpcheck_extra && $(CMAKE_COMMAND) -P CMakeFiles\bumpcheck_extra.dir\cmake_clean.cmake
.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/clean

bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\code\bumptest E:\code\bumptest\bumpcheck_extra E:\code\bumptest E:\code\bumptest\bumpcheck_extra E:\code\bumptest\bumpcheck_extra\CMakeFiles\bumpcheck_extra.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : bumpcheck_extra/CMakeFiles/bumpcheck_extra.dir/depend


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
include bumpcheck/CMakeFiles/bumpcheck.dir/depend.make

# Include the progress variables for this target.
include bumpcheck/CMakeFiles/bumpcheck.dir/progress.make

# Include the compile flags for this target's objects.
include bumpcheck/CMakeFiles/bumpcheck.dir/flags.make

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/flags.make
bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/includes_CXX.rsp
bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj: bumpcheck/bumpchecker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bumpcheck.dir\bumpchecker.cpp.obj -c E:\code\bumptest\bumpcheck\bumpchecker.cpp

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bumpcheck.dir/bumpchecker.cpp.i"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\code\bumptest\bumpcheck\bumpchecker.cpp > CMakeFiles\bumpcheck.dir\bumpchecker.cpp.i

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bumpcheck.dir/bumpchecker.cpp.s"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\code\bumptest\bumpcheck\bumpchecker.cpp -o CMakeFiles\bumpcheck.dir\bumpchecker.cpp.s

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.requires:

.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.requires

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.provides: bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.requires
	$(MAKE) -f bumpcheck\CMakeFiles\bumpcheck.dir\build.make bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.provides.build
.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.provides

bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.provides.build: bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj


bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/flags.make
bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/includes_CXX.rsp
bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj: bumpcheck/control.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bumpcheck.dir\control.cpp.obj -c E:\code\bumptest\bumpcheck\control.cpp

bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bumpcheck.dir/control.cpp.i"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\code\bumptest\bumpcheck\control.cpp > CMakeFiles\bumpcheck.dir\control.cpp.i

bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bumpcheck.dir/control.cpp.s"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\code\bumptest\bumpcheck\control.cpp -o CMakeFiles\bumpcheck.dir\control.cpp.s

bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.requires:

.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.requires

bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.provides: bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.requires
	$(MAKE) -f bumpcheck\CMakeFiles\bumpcheck.dir\build.make bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.provides.build
.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.provides

bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.provides.build: bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj


bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/flags.make
bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj: bumpcheck/CMakeFiles/bumpcheck.dir/includes_CXX.rsp
bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj: bumpcheck/item.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bumpcheck.dir\item.cpp.obj -c E:\code\bumptest\bumpcheck\item.cpp

bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bumpcheck.dir/item.cpp.i"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\code\bumptest\bumpcheck\item.cpp > CMakeFiles\bumpcheck.dir\item.cpp.i

bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bumpcheck.dir/item.cpp.s"
	cd /d E:\code\bumptest\bumpcheck && E:\code_package\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\code\bumptest\bumpcheck\item.cpp -o CMakeFiles\bumpcheck.dir\item.cpp.s

bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.requires:

.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.requires

bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.provides: bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.requires
	$(MAKE) -f bumpcheck\CMakeFiles\bumpcheck.dir\build.make bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.provides.build
.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.provides

bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.provides.build: bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj


# Object files for target bumpcheck
bumpcheck_OBJECTS = \
"CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj" \
"CMakeFiles/bumpcheck.dir/control.cpp.obj" \
"CMakeFiles/bumpcheck.dir/item.cpp.obj"

# External object files for target bumpcheck
bumpcheck_EXTERNAL_OBJECTS =

lib/libbumpcheck.a: bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj
lib/libbumpcheck.a: bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj
lib/libbumpcheck.a: bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj
lib/libbumpcheck.a: bumpcheck/CMakeFiles/bumpcheck.dir/build.make
lib/libbumpcheck.a: bumpcheck/CMakeFiles/bumpcheck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\code\bumptest\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ..\lib\libbumpcheck.a"
	cd /d E:\code\bumptest\bumpcheck && $(CMAKE_COMMAND) -P CMakeFiles\bumpcheck.dir\cmake_clean_target.cmake
	cd /d E:\code\bumptest\bumpcheck && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bumpcheck.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bumpcheck/CMakeFiles/bumpcheck.dir/build: lib/libbumpcheck.a

.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/build

bumpcheck/CMakeFiles/bumpcheck.dir/requires: bumpcheck/CMakeFiles/bumpcheck.dir/bumpchecker.cpp.obj.requires
bumpcheck/CMakeFiles/bumpcheck.dir/requires: bumpcheck/CMakeFiles/bumpcheck.dir/control.cpp.obj.requires
bumpcheck/CMakeFiles/bumpcheck.dir/requires: bumpcheck/CMakeFiles/bumpcheck.dir/item.cpp.obj.requires

.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/requires

bumpcheck/CMakeFiles/bumpcheck.dir/clean:
	cd /d E:\code\bumptest\bumpcheck && $(CMAKE_COMMAND) -P CMakeFiles\bumpcheck.dir\cmake_clean.cmake
.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/clean

bumpcheck/CMakeFiles/bumpcheck.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\code\bumptest E:\code\bumptest\bumpcheck E:\code\bumptest E:\code\bumptest\bumpcheck E:\code\bumptest\bumpcheck\CMakeFiles\bumpcheck.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : bumpcheck/CMakeFiles/bumpcheck.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build"

# Include any dependencies generated for this target.
include CMakeFiles/c2ga.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/c2ga.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c2ga.dir/flags.make

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o: CMakeFiles/c2ga.dir/flags.make
CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o: ../src/c2ga/Mvec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o -c "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Mvec.cpp"

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Mvec.cpp" > CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.i

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/src/c2ga/Mvec.cpp" -o CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.s

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.requires:

.PHONY : CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.requires

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.provides: CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.requires
	$(MAKE) -f CMakeFiles/c2ga.dir/build.make CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.provides.build
.PHONY : CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.provides

CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.provides.build: CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o


# Object files for target c2ga
c2ga_OBJECTS = \
"CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o"

# External object files for target c2ga
c2ga_EXTERNAL_OBJECTS =

libc2ga.so: CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o
libc2ga.so: CMakeFiles/c2ga.dir/build.make
libc2ga.so: CMakeFiles/c2ga.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libc2ga.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c2ga.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c2ga.dir/build: libc2ga.so

.PHONY : CMakeFiles/c2ga.dir/build

CMakeFiles/c2ga.dir/requires: CMakeFiles/c2ga.dir/src/c2ga/Mvec.cpp.o.requires

.PHONY : CMakeFiles/c2ga.dir/requires

CMakeFiles/c2ga.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/c2ga.dir/cmake_clean.cmake
.PHONY : CMakeFiles/c2ga.dir/clean

CMakeFiles/c2ga.dir/depend:
	cd "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga" "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga" "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build" "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build" "/mnt/d/Florian Torres/Documents/Projects/ga-raytracer/lib/garamon_c2ga/build/CMakeFiles/c2ga.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/c2ga.dir/depend


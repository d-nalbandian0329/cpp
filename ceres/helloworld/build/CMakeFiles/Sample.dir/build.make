# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/takeshi/Program/C++/ceres/helloworld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/takeshi/Program/C++/ceres/helloworld/build

# Include any dependencies generated for this target.
include CMakeFiles/Sample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sample.dir/flags.make

CMakeFiles/Sample.dir/main.cpp.o: CMakeFiles/Sample.dir/flags.make
CMakeFiles/Sample.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/takeshi/Program/C++/ceres/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Sample.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sample.dir/main.cpp.o -c /home/takeshi/Program/C++/ceres/helloworld/main.cpp

CMakeFiles/Sample.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sample.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/takeshi/Program/C++/ceres/helloworld/main.cpp > CMakeFiles/Sample.dir/main.cpp.i

CMakeFiles/Sample.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sample.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/takeshi/Program/C++/ceres/helloworld/main.cpp -o CMakeFiles/Sample.dir/main.cpp.s

CMakeFiles/Sample.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Sample.dir/main.cpp.o.requires

CMakeFiles/Sample.dir/main.cpp.o.provides: CMakeFiles/Sample.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Sample.dir/build.make CMakeFiles/Sample.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Sample.dir/main.cpp.o.provides

CMakeFiles/Sample.dir/main.cpp.o.provides.build: CMakeFiles/Sample.dir/main.cpp.o


# Object files for target Sample
Sample_OBJECTS = \
"CMakeFiles/Sample.dir/main.cpp.o"

# External object files for target Sample
Sample_EXTERNAL_OBJECTS =

Sample: CMakeFiles/Sample.dir/main.cpp.o
Sample: CMakeFiles/Sample.dir/build.make
Sample: /usr/local/lib/libceres.a
Sample: /usr/lib/x86_64-linux-gnu/libglog.so
Sample: /usr/lib/x86_64-linux-gnu/libgflags.so
Sample: /usr/lib/x86_64-linux-gnu/libspqr.so
Sample: /usr/lib/x86_64-linux-gnu/libcholmod.so
Sample: /usr/lib/x86_64-linux-gnu/libccolamd.so
Sample: /usr/lib/x86_64-linux-gnu/libcamd.so
Sample: /usr/lib/x86_64-linux-gnu/libcolamd.so
Sample: /usr/lib/x86_64-linux-gnu/libamd.so
Sample: /usr/lib/liblapack.so
Sample: /usr/lib/libf77blas.so
Sample: /usr/lib/libatlas.so
Sample: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
Sample: /usr/lib/x86_64-linux-gnu/librt.so
Sample: /usr/lib/x86_64-linux-gnu/libcxsparse.so
Sample: /usr/lib/liblapack.so
Sample: /usr/lib/libf77blas.so
Sample: /usr/lib/libatlas.so
Sample: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
Sample: /usr/lib/x86_64-linux-gnu/librt.so
Sample: /usr/lib/x86_64-linux-gnu/libcxsparse.so
Sample: CMakeFiles/Sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/takeshi/Program/C++/ceres/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Sample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sample.dir/build: Sample

.PHONY : CMakeFiles/Sample.dir/build

CMakeFiles/Sample.dir/requires: CMakeFiles/Sample.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Sample.dir/requires

CMakeFiles/Sample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Sample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Sample.dir/clean

CMakeFiles/Sample.dir/depend:
	cd /home/takeshi/Program/C++/ceres/helloworld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/takeshi/Program/C++/ceres/helloworld /home/takeshi/Program/C++/ceres/helloworld /home/takeshi/Program/C++/ceres/helloworld/build /home/takeshi/Program/C++/ceres/helloworld/build /home/takeshi/Program/C++/ceres/helloworld/build/CMakeFiles/Sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sample.dir/depend

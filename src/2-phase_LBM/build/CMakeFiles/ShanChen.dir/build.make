# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build

# Include any dependencies generated for this target.
include CMakeFiles/ShanChen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ShanChen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ShanChen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ShanChen.dir/flags.make

CMakeFiles/ShanChen.dir/ShanChen.cpp.o: CMakeFiles/ShanChen.dir/flags.make
CMakeFiles/ShanChen.dir/ShanChen.cpp.o: ../ShanChen.cpp
CMakeFiles/ShanChen.dir/ShanChen.cpp.o: CMakeFiles/ShanChen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ShanChen.dir/ShanChen.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShanChen.dir/ShanChen.cpp.o -MF CMakeFiles/ShanChen.dir/ShanChen.cpp.o.d -o CMakeFiles/ShanChen.dir/ShanChen.cpp.o -c /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/ShanChen.cpp

CMakeFiles/ShanChen.dir/ShanChen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ShanChen.dir/ShanChen.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/ShanChen.cpp > CMakeFiles/ShanChen.dir/ShanChen.cpp.i

CMakeFiles/ShanChen.dir/ShanChen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ShanChen.dir/ShanChen.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/ShanChen.cpp -o CMakeFiles/ShanChen.dir/ShanChen.cpp.s

# Object files for target ShanChen
ShanChen_OBJECTS = \
"CMakeFiles/ShanChen.dir/ShanChen.cpp.o"

# External object files for target ShanChen
ShanChen_EXTERNAL_OBJECTS =

../ShanChen: CMakeFiles/ShanChen.dir/ShanChen.cpp.o
../ShanChen: CMakeFiles/ShanChen.dir/build.make
../ShanChen: libpalabos.a
../ShanChen: /opt/intel/oneapi/mpi/2021.8.0/lib/libmpicxx.so
../ShanChen: /opt/intel/oneapi/mpi/2021.8.0/lib/release/libmpi.so
../ShanChen: /usr/lib/x86_64-linux-gnu/librt.a
../ShanChen: /usr/lib/x86_64-linux-gnu/libpthread.a
../ShanChen: /usr/lib/x86_64-linux-gnu/libdl.a
../ShanChen: CMakeFiles/ShanChen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../ShanChen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ShanChen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ShanChen.dir/build: ../ShanChen
.PHONY : CMakeFiles/ShanChen.dir/build

CMakeFiles/ShanChen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ShanChen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ShanChen.dir/clean

CMakeFiles/ShanChen.dir/depend:
	cd /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build /mnt/data2/windowkim/hyundai/lbm/MPLBM-UT/src/2-phase_LBM/build/CMakeFiles/ShanChen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ShanChen.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /media/tokoyama/Data/Downloads/clion-2021.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /media/tokoyama/Data/Downloads/clion-2021.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tokoyama/Documents/OS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tokoyama/Documents/OS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OS.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/OS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS.dir/flags.make

CMakeFiles/OS.dir/main.c.o: CMakeFiles/OS.dir/flags.make
CMakeFiles/OS.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OS.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS.dir/main.c.o -c /home/tokoyama/Documents/OS/main.c

CMakeFiles/OS.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tokoyama/Documents/OS/main.c > CMakeFiles/OS.dir/main.c.i

CMakeFiles/OS.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tokoyama/Documents/OS/main.c -o CMakeFiles/OS.dir/main.c.s

CMakeFiles/OS.dir/c1.c.o: CMakeFiles/OS.dir/flags.make
CMakeFiles/OS.dir/c1.c.o: ../c1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OS.dir/c1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS.dir/c1.c.o -c /home/tokoyama/Documents/OS/c1.c

CMakeFiles/OS.dir/c1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS.dir/c1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tokoyama/Documents/OS/c1.c > CMakeFiles/OS.dir/c1.c.i

CMakeFiles/OS.dir/c1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS.dir/c1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tokoyama/Documents/OS/c1.c -o CMakeFiles/OS.dir/c1.c.s

CMakeFiles/OS.dir/c2.c.o: CMakeFiles/OS.dir/flags.make
CMakeFiles/OS.dir/c2.c.o: ../c2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OS.dir/c2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS.dir/c2.c.o -c /home/tokoyama/Documents/OS/c2.c

CMakeFiles/OS.dir/c2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS.dir/c2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tokoyama/Documents/OS/c2.c > CMakeFiles/OS.dir/c2.c.i

CMakeFiles/OS.dir/c2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS.dir/c2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tokoyama/Documents/OS/c2.c -o CMakeFiles/OS.dir/c2.c.s

CMakeFiles/OS.dir/c3.c.o: CMakeFiles/OS.dir/flags.make
CMakeFiles/OS.dir/c3.c.o: ../c3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OS.dir/c3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS.dir/c3.c.o -c /home/tokoyama/Documents/OS/c3.c

CMakeFiles/OS.dir/c3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS.dir/c3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tokoyama/Documents/OS/c3.c > CMakeFiles/OS.dir/c3.c.i

CMakeFiles/OS.dir/c3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS.dir/c3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tokoyama/Documents/OS/c3.c -o CMakeFiles/OS.dir/c3.c.s

# Object files for target OS
OS_OBJECTS = \
"CMakeFiles/OS.dir/main.c.o" \
"CMakeFiles/OS.dir/c1.c.o" \
"CMakeFiles/OS.dir/c2.c.o" \
"CMakeFiles/OS.dir/c3.c.o"

# External object files for target OS
OS_EXTERNAL_OBJECTS =

OS: CMakeFiles/OS.dir/main.c.o
OS: CMakeFiles/OS.dir/c1.c.o
OS: CMakeFiles/OS.dir/c2.c.o
OS: CMakeFiles/OS.dir/c3.c.o
OS: CMakeFiles/OS.dir/build.make
OS: CMakeFiles/OS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable OS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS.dir/build: OS
.PHONY : CMakeFiles/OS.dir/build

CMakeFiles/OS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OS.dir/clean

CMakeFiles/OS.dir/depend:
	cd /home/tokoyama/Documents/OS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tokoyama/Documents/OS /home/tokoyama/Documents/OS /home/tokoyama/Documents/OS/cmake-build-debug /home/tokoyama/Documents/OS/cmake-build-debug /home/tokoyama/Documents/OS/cmake-build-debug/CMakeFiles/OS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OS.dir/depend


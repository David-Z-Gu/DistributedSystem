# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yuniemao/Documents/CS5450/DistributedSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DistributedSystem.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DistributedSystem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DistributedSystem.dir/flags.make

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o: CMakeFiles/DistributedSystem.dir/flags.make
CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o: ../starter_code/echo_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o   -c /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_client.c

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_client.c > CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.i

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_client.c -o CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.s

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.requires:

.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.requires

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.provides: CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.requires
	$(MAKE) -f CMakeFiles/DistributedSystem.dir/build.make CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.provides.build
.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.provides

CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.provides.build: CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o


CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o: CMakeFiles/DistributedSystem.dir/flags.make
CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o: ../starter_code/echo_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o   -c /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_server.c

CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_server.c > CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.i

CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/echo_server.c -o CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.s

CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.requires:

.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.requires

CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.provides: CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.requires
	$(MAKE) -f CMakeFiles/DistributedSystem.dir/build.make CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.provides.build
.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.provides

CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.provides.build: CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o


CMakeFiles/DistributedSystem.dir/starter_code/log.c.o: CMakeFiles/DistributedSystem.dir/flags.make
CMakeFiles/DistributedSystem.dir/starter_code/log.c.o: ../starter_code/log.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/DistributedSystem.dir/starter_code/log.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DistributedSystem.dir/starter_code/log.c.o   -c /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/log.c

CMakeFiles/DistributedSystem.dir/starter_code/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DistributedSystem.dir/starter_code/log.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/log.c > CMakeFiles/DistributedSystem.dir/starter_code/log.c.i

CMakeFiles/DistributedSystem.dir/starter_code/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DistributedSystem.dir/starter_code/log.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/log.c -o CMakeFiles/DistributedSystem.dir/starter_code/log.c.s

CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.requires:

.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.requires

CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.provides: CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.requires
	$(MAKE) -f CMakeFiles/DistributedSystem.dir/build.make CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.provides.build
.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.provides

CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.provides.build: CMakeFiles/DistributedSystem.dir/starter_code/log.c.o


CMakeFiles/DistributedSystem.dir/starter_code/server.c.o: CMakeFiles/DistributedSystem.dir/flags.make
CMakeFiles/DistributedSystem.dir/starter_code/server.c.o: ../starter_code/server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/DistributedSystem.dir/starter_code/server.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DistributedSystem.dir/starter_code/server.c.o   -c /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/server.c

CMakeFiles/DistributedSystem.dir/starter_code/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DistributedSystem.dir/starter_code/server.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/server.c > CMakeFiles/DistributedSystem.dir/starter_code/server.c.i

CMakeFiles/DistributedSystem.dir/starter_code/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DistributedSystem.dir/starter_code/server.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yuniemao/Documents/CS5450/DistributedSystem/starter_code/server.c -o CMakeFiles/DistributedSystem.dir/starter_code/server.c.s

CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.requires:

.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.requires

CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.provides: CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.requires
	$(MAKE) -f CMakeFiles/DistributedSystem.dir/build.make CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.provides.build
.PHONY : CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.provides

CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.provides.build: CMakeFiles/DistributedSystem.dir/starter_code/server.c.o


# Object files for target DistributedSystem
DistributedSystem_OBJECTS = \
"CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o" \
"CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o" \
"CMakeFiles/DistributedSystem.dir/starter_code/log.c.o" \
"CMakeFiles/DistributedSystem.dir/starter_code/server.c.o"

# External object files for target DistributedSystem
DistributedSystem_EXTERNAL_OBJECTS =

DistributedSystem: CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o
DistributedSystem: CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o
DistributedSystem: CMakeFiles/DistributedSystem.dir/starter_code/log.c.o
DistributedSystem: CMakeFiles/DistributedSystem.dir/starter_code/server.c.o
DistributedSystem: CMakeFiles/DistributedSystem.dir/build.make
DistributedSystem: CMakeFiles/DistributedSystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable DistributedSystem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DistributedSystem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DistributedSystem.dir/build: DistributedSystem

.PHONY : CMakeFiles/DistributedSystem.dir/build

CMakeFiles/DistributedSystem.dir/requires: CMakeFiles/DistributedSystem.dir/starter_code/echo_client.c.o.requires
CMakeFiles/DistributedSystem.dir/requires: CMakeFiles/DistributedSystem.dir/starter_code/echo_server.c.o.requires
CMakeFiles/DistributedSystem.dir/requires: CMakeFiles/DistributedSystem.dir/starter_code/log.c.o.requires
CMakeFiles/DistributedSystem.dir/requires: CMakeFiles/DistributedSystem.dir/starter_code/server.c.o.requires

.PHONY : CMakeFiles/DistributedSystem.dir/requires

CMakeFiles/DistributedSystem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DistributedSystem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DistributedSystem.dir/clean

CMakeFiles/DistributedSystem.dir/depend:
	cd /Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yuniemao/Documents/CS5450/DistributedSystem /Users/yuniemao/Documents/CS5450/DistributedSystem /Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug /Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug /Users/yuniemao/Documents/CS5450/DistributedSystem/cmake-build-debug/CMakeFiles/DistributedSystem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DistributedSystem.dir/depend


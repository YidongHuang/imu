# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/nvidia/imu/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/imu/src

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nvidia/imu/src/CMakeFiles /home/nvidia/imu/src/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nvidia/imu/src/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named motion

# Build rule for target.
motion: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 motion
.PHONY : motion

# fast build rule for target.
motion/fast:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/build
.PHONY : motion/fast

appControlHandler.o: appControlHandler.c.o

.PHONY : appControlHandler.o

# target to build an object file
appControlHandler.c.o:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/appControlHandler.c.o
.PHONY : appControlHandler.c.o

appControlHandler.i: appControlHandler.c.i

.PHONY : appControlHandler.i

# target to preprocess a source file
appControlHandler.c.i:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/appControlHandler.c.i
.PHONY : appControlHandler.c.i

appControlHandler.s: appControlHandler.c.s

.PHONY : appControlHandler.s

# target to generate assembly for a file
appControlHandler.c.s:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/appControlHandler.c.s
.PHONY : appControlHandler.c.s

motion_example.o: motion_example.c.o

.PHONY : motion_example.o

# target to build an object file
motion_example.c.o:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/motion_example.c.o
.PHONY : motion_example.c.o

motion_example.i: motion_example.c.i

.PHONY : motion_example.i

# target to preprocess a source file
motion_example.c.i:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/motion_example.c.i
.PHONY : motion_example.c.i

motion_example.s: motion_example.c.s

.PHONY : motion_example.s

# target to generate assembly for a file
motion_example.c.s:
	$(MAKE) -f CMakeFiles/motion.dir/build.make CMakeFiles/motion.dir/motion_example.c.s
.PHONY : motion_example.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... motion"
	@echo "... appControlHandler.o"
	@echo "... appControlHandler.i"
	@echo "... appControlHandler.s"
	@echo "... motion_example.o"
	@echo "... motion_example.i"
	@echo "... motion_example.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


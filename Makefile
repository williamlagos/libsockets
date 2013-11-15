# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_SOURCE_DIR = /home/william/sockets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/william/sockets

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/william/sockets/CMakeFiles /home/william/sockets/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/william/sockets/CMakeFiles 0
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
# Target rules for targets named client

# Build rule for target.
client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client
.PHONY : client

# fast build rule for target.
client/fast:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/build
.PHONY : client/fast

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/build
.PHONY : server/fast

#=============================================================================
# Target rules for targets named sockets

# Build rule for target.
sockets: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sockets
.PHONY : sockets

# fast build rule for target.
sockets/fast:
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/build
.PHONY : sockets/fast

#=============================================================================
# Target rules for targets named sockets-static

# Build rule for target.
sockets-static: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sockets-static
.PHONY : sockets-static

# fast build rule for target.
sockets-static/fast:
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/build
.PHONY : sockets-static/fast

src/client.o: src/client.c.o
.PHONY : src/client.o

# target to build an object file
src/client.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/client.c.o
.PHONY : src/client.c.o

src/client.i: src/client.c.i
.PHONY : src/client.i

# target to preprocess a source file
src/client.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/client.c.i
.PHONY : src/client.c.i

src/client.s: src/client.c.s
.PHONY : src/client.s

# target to generate assembly for a file
src/client.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/client.c.s
.PHONY : src/client.c.s

src/server.o: src/server.c.o
.PHONY : src/server.o

# target to build an object file
src/server.c.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/server.c.o
.PHONY : src/server.c.o

src/server.i: src/server.c.i
.PHONY : src/server.i

# target to preprocess a source file
src/server.c.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/server.c.i
.PHONY : src/server.c.i

src/server.s: src/server.c.s
.PHONY : src/server.s

# target to generate assembly for a file
src/server.c.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/server.c.s
.PHONY : src/server.c.s

src/sockets.o: src/sockets.c.o
.PHONY : src/sockets.o

# target to build an object file
src/sockets.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/sockets.c.o
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/sockets.c.o
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/sockets.c.o
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/sockets.c.o
.PHONY : src/sockets.c.o

src/sockets.i: src/sockets.c.i
.PHONY : src/sockets.i

# target to preprocess a source file
src/sockets.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/sockets.c.i
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/sockets.c.i
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/sockets.c.i
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/sockets.c.i
.PHONY : src/sockets.c.i

src/sockets.s: src/sockets.c.s
.PHONY : src/sockets.s

# target to generate assembly for a file
src/sockets.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/sockets.c.s
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/sockets.c.s
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/sockets.c.s
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/sockets.c.s
.PHONY : src/sockets.c.s

src/structs.o: src/structs.c.o
.PHONY : src/structs.o

# target to build an object file
src/structs.c.o:
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/structs.c.o
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/structs.c.o
.PHONY : src/structs.c.o

src/structs.i: src/structs.c.i
.PHONY : src/structs.i

# target to preprocess a source file
src/structs.c.i:
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/structs.c.i
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/structs.c.i
.PHONY : src/structs.c.i

src/structs.s: src/structs.c.s
.PHONY : src/structs.s

# target to generate assembly for a file
src/structs.c.s:
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/src/structs.c.s
	$(MAKE) -f CMakeFiles/sockets-static.dir/build.make CMakeFiles/sockets-static.dir/src/structs.c.s
.PHONY : src/structs.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... client"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... server"
	@echo "... sockets"
	@echo "... sockets-static"
	@echo "... src/client.o"
	@echo "... src/client.i"
	@echo "... src/client.s"
	@echo "... src/server.o"
	@echo "... src/server.i"
	@echo "... src/server.s"
	@echo "... src/sockets.o"
	@echo "... src/sockets.i"
	@echo "... src/sockets.s"
	@echo "... src/structs.o"
	@echo "... src/structs.i"
	@echo "... src/structs.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


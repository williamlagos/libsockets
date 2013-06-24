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
# Target rules for targets named sockets_static

# Build rule for target.
sockets_static: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sockets_static
.PHONY : sockets_static

# fast build rule for target.
sockets_static/fast:
	$(MAKE) -f CMakeFiles/sockets_static.dir/build.make CMakeFiles/sockets_static.dir/build
.PHONY : sockets_static/fast

client.o: client.c.o
.PHONY : client.o

# target to build an object file
client.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.o
.PHONY : client.c.o

client.i: client.c.i
.PHONY : client.i

# target to preprocess a source file
client.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.i
.PHONY : client.c.i

client.s: client.c.s
.PHONY : client.s

# target to generate assembly for a file
client.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.s
.PHONY : client.c.s

server.o: server.c.o
.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i
.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s
.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.s
.PHONY : server.c.s

sockets.o: sockets.c.o
.PHONY : sockets.o

# target to build an object file
sockets.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/sockets.c.o
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/sockets.c.o
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/sockets.c.o
	$(MAKE) -f CMakeFiles/sockets_static.dir/build.make CMakeFiles/sockets_static.dir/sockets.c.o
.PHONY : sockets.c.o

sockets.i: sockets.c.i
.PHONY : sockets.i

# target to preprocess a source file
sockets.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/sockets.c.i
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/sockets.c.i
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/sockets.c.i
	$(MAKE) -f CMakeFiles/sockets_static.dir/build.make CMakeFiles/sockets_static.dir/sockets.c.i
.PHONY : sockets.c.i

sockets.s: sockets.c.s
.PHONY : sockets.s

# target to generate assembly for a file
sockets.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/sockets.c.s
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/sockets.c.s
	$(MAKE) -f CMakeFiles/sockets.dir/build.make CMakeFiles/sockets.dir/sockets.c.s
	$(MAKE) -f CMakeFiles/sockets_static.dir/build.make CMakeFiles/sockets_static.dir/sockets.c.s
.PHONY : sockets.c.s

structs.o: structs.c.o
.PHONY : structs.o

# target to build an object file
structs.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/structs.c.o
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/structs.c.o
.PHONY : structs.c.o

structs.i: structs.c.i
.PHONY : structs.i

# target to preprocess a source file
structs.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/structs.c.i
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/structs.c.i
.PHONY : structs.c.i

structs.s: structs.c.s
.PHONY : structs.s

# target to generate assembly for a file
structs.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/structs.c.s
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/structs.c.s
.PHONY : structs.c.s

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
	@echo "... sockets_static"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... sockets.o"
	@echo "... sockets.i"
	@echo "... sockets.s"
	@echo "... structs.o"
	@echo "... structs.i"
	@echo "... structs.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


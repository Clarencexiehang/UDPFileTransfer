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
CMAKE_SOURCE_DIR = /root/code/download/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/code/download/Server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/main.cpp.o: ../main.cpp
CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Server.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/main.cpp.o -MF CMakeFiles/Server.dir/main.cpp.o.d -o CMakeFiles/Server.dir/main.cpp.o -c /root/code/download/Server/main.cpp

CMakeFiles/Server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/main.cpp > CMakeFiles/Server.dir/main.cpp.i

CMakeFiles/Server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/main.cpp -o CMakeFiles/Server.dir/main.cpp.s

CMakeFiles/Server.dir/Service/ServerService.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Service/ServerService.cpp.o: ../Service/ServerService.cpp
CMakeFiles/Server.dir/Service/ServerService.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/Service/ServerService.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Service/ServerService.cpp.o -MF CMakeFiles/Server.dir/Service/ServerService.cpp.o.d -o CMakeFiles/Server.dir/Service/ServerService.cpp.o -c /root/code/download/Server/Service/ServerService.cpp

CMakeFiles/Server.dir/Service/ServerService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Service/ServerService.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Service/ServerService.cpp > CMakeFiles/Server.dir/Service/ServerService.cpp.i

CMakeFiles/Server.dir/Service/ServerService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Service/ServerService.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Service/ServerService.cpp -o CMakeFiles/Server.dir/Service/ServerService.cpp.s

CMakeFiles/Server.dir/Util/MD5Util.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Util/MD5Util.cpp.o: ../Util/MD5Util.cpp
CMakeFiles/Server.dir/Util/MD5Util.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/Util/MD5Util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Util/MD5Util.cpp.o -MF CMakeFiles/Server.dir/Util/MD5Util.cpp.o.d -o CMakeFiles/Server.dir/Util/MD5Util.cpp.o -c /root/code/download/Server/Util/MD5Util.cpp

CMakeFiles/Server.dir/Util/MD5Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Util/MD5Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Util/MD5Util.cpp > CMakeFiles/Server.dir/Util/MD5Util.cpp.i

CMakeFiles/Server.dir/Util/MD5Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Util/MD5Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Util/MD5Util.cpp -o CMakeFiles/Server.dir/Util/MD5Util.cpp.s

CMakeFiles/Server.dir/Controller/WebServer.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Controller/WebServer.cpp.o: ../Controller/WebServer.cpp
CMakeFiles/Server.dir/Controller/WebServer.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Server.dir/Controller/WebServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Controller/WebServer.cpp.o -MF CMakeFiles/Server.dir/Controller/WebServer.cpp.o.d -o CMakeFiles/Server.dir/Controller/WebServer.cpp.o -c /root/code/download/Server/Controller/WebServer.cpp

CMakeFiles/Server.dir/Controller/WebServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Controller/WebServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Controller/WebServer.cpp > CMakeFiles/Server.dir/Controller/WebServer.cpp.i

CMakeFiles/Server.dir/Controller/WebServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Controller/WebServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Controller/WebServer.cpp -o CMakeFiles/Server.dir/Controller/WebServer.cpp.s

CMakeFiles/Server.dir/Dao/UserMapper.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Dao/UserMapper.cpp.o: ../Dao/UserMapper.cpp
CMakeFiles/Server.dir/Dao/UserMapper.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Server.dir/Dao/UserMapper.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Dao/UserMapper.cpp.o -MF CMakeFiles/Server.dir/Dao/UserMapper.cpp.o.d -o CMakeFiles/Server.dir/Dao/UserMapper.cpp.o -c /root/code/download/Server/Dao/UserMapper.cpp

CMakeFiles/Server.dir/Dao/UserMapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Dao/UserMapper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Dao/UserMapper.cpp > CMakeFiles/Server.dir/Dao/UserMapper.cpp.i

CMakeFiles/Server.dir/Dao/UserMapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Dao/UserMapper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Dao/UserMapper.cpp -o CMakeFiles/Server.dir/Dao/UserMapper.cpp.s

CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o: ../Service/DynamicallyAdjustNetwork.cpp
CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o -MF CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o.d -o CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o -c /root/code/download/Server/Service/DynamicallyAdjustNetwork.cpp

CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Service/DynamicallyAdjustNetwork.cpp > CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.i

CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Service/DynamicallyAdjustNetwork.cpp -o CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.s

CMakeFiles/Server.dir/Service/NetControl.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Service/NetControl.cpp.o: ../Service/NetControl.cpp
CMakeFiles/Server.dir/Service/NetControl.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Server.dir/Service/NetControl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Service/NetControl.cpp.o -MF CMakeFiles/Server.dir/Service/NetControl.cpp.o.d -o CMakeFiles/Server.dir/Service/NetControl.cpp.o -c /root/code/download/Server/Service/NetControl.cpp

CMakeFiles/Server.dir/Service/NetControl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Service/NetControl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Service/NetControl.cpp > CMakeFiles/Server.dir/Service/NetControl.cpp.i

CMakeFiles/Server.dir/Service/NetControl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Service/NetControl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Service/NetControl.cpp -o CMakeFiles/Server.dir/Service/NetControl.cpp.s

CMakeFiles/Server.dir/Util/crsa.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Util/crsa.cpp.o: ../Util/crsa.cpp
CMakeFiles/Server.dir/Util/crsa.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Server.dir/Util/crsa.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Util/crsa.cpp.o -MF CMakeFiles/Server.dir/Util/crsa.cpp.o.d -o CMakeFiles/Server.dir/Util/crsa.cpp.o -c /root/code/download/Server/Util/crsa.cpp

CMakeFiles/Server.dir/Util/crsa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Util/crsa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/download/Server/Util/crsa.cpp > CMakeFiles/Server.dir/Util/crsa.cpp.i

CMakeFiles/Server.dir/Util/crsa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Util/crsa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/download/Server/Util/crsa.cpp -o CMakeFiles/Server.dir/Util/crsa.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/main.cpp.o" \
"CMakeFiles/Server.dir/Service/ServerService.cpp.o" \
"CMakeFiles/Server.dir/Util/MD5Util.cpp.o" \
"CMakeFiles/Server.dir/Controller/WebServer.cpp.o" \
"CMakeFiles/Server.dir/Dao/UserMapper.cpp.o" \
"CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o" \
"CMakeFiles/Server.dir/Service/NetControl.cpp.o" \
"CMakeFiles/Server.dir/Util/crsa.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/main.cpp.o
Server: CMakeFiles/Server.dir/Service/ServerService.cpp.o
Server: CMakeFiles/Server.dir/Util/MD5Util.cpp.o
Server: CMakeFiles/Server.dir/Controller/WebServer.cpp.o
Server: CMakeFiles/Server.dir/Dao/UserMapper.cpp.o
Server: CMakeFiles/Server.dir/Service/DynamicallyAdjustNetwork.cpp.o
Server: CMakeFiles/Server.dir/Service/NetControl.cpp.o
Server: CMakeFiles/Server.dir/Util/crsa.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: /usr/local/lib/libworkflow.so
Server: /usr/local/lib/libwfrest.so
Server: /usr/lib/x86_64-linux-gnu/libz.so
Server: /usr/lib/x86_64-linux-gnu/libssl.so
Server: /usr/lib/x86_64-linux-gnu/libcrypto.so
Server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/code/download/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server
.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /root/code/download/Server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/download/Server /root/code/download/Server /root/code/download/Server/cmake-build-debug /root/code/download/Server/cmake-build-debug /root/code/download/Server/cmake-build-debug/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend


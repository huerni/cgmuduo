# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cgMuduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cgMuduo/build

# Include any dependencies generated for this target.
include CMakeFiles/cgmuduo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cgmuduo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cgmuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cgmuduo.dir/flags.make

CMakeFiles/cgmuduo.dir/Acceptor.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Acceptor.o: ../Acceptor.cc
CMakeFiles/cgmuduo.dir/Acceptor.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cgmuduo.dir/Acceptor.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Acceptor.o -MF CMakeFiles/cgmuduo.dir/Acceptor.o.d -o CMakeFiles/cgmuduo.dir/Acceptor.o -c /home/cgMuduo/Acceptor.cc

CMakeFiles/cgmuduo.dir/Acceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Acceptor.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Acceptor.cc > CMakeFiles/cgmuduo.dir/Acceptor.i

CMakeFiles/cgmuduo.dir/Acceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Acceptor.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Acceptor.cc -o CMakeFiles/cgmuduo.dir/Acceptor.s

CMakeFiles/cgmuduo.dir/Buffer.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Buffer.o: ../Buffer.cc
CMakeFiles/cgmuduo.dir/Buffer.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cgmuduo.dir/Buffer.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Buffer.o -MF CMakeFiles/cgmuduo.dir/Buffer.o.d -o CMakeFiles/cgmuduo.dir/Buffer.o -c /home/cgMuduo/Buffer.cc

CMakeFiles/cgmuduo.dir/Buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Buffer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Buffer.cc > CMakeFiles/cgmuduo.dir/Buffer.i

CMakeFiles/cgmuduo.dir/Buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Buffer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Buffer.cc -o CMakeFiles/cgmuduo.dir/Buffer.s

CMakeFiles/cgmuduo.dir/Channel.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Channel.o: ../Channel.cc
CMakeFiles/cgmuduo.dir/Channel.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cgmuduo.dir/Channel.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Channel.o -MF CMakeFiles/cgmuduo.dir/Channel.o.d -o CMakeFiles/cgmuduo.dir/Channel.o -c /home/cgMuduo/Channel.cc

CMakeFiles/cgmuduo.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Channel.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Channel.cc > CMakeFiles/cgmuduo.dir/Channel.i

CMakeFiles/cgmuduo.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Channel.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Channel.cc -o CMakeFiles/cgmuduo.dir/Channel.s

CMakeFiles/cgmuduo.dir/CurrentThread.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/CurrentThread.o: ../CurrentThread.cc
CMakeFiles/cgmuduo.dir/CurrentThread.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cgmuduo.dir/CurrentThread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/CurrentThread.o -MF CMakeFiles/cgmuduo.dir/CurrentThread.o.d -o CMakeFiles/cgmuduo.dir/CurrentThread.o -c /home/cgMuduo/CurrentThread.cc

CMakeFiles/cgmuduo.dir/CurrentThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/CurrentThread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/CurrentThread.cc > CMakeFiles/cgmuduo.dir/CurrentThread.i

CMakeFiles/cgmuduo.dir/CurrentThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/CurrentThread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/CurrentThread.cc -o CMakeFiles/cgmuduo.dir/CurrentThread.s

CMakeFiles/cgmuduo.dir/DefaultPoller.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/DefaultPoller.o: ../DefaultPoller.cc
CMakeFiles/cgmuduo.dir/DefaultPoller.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cgmuduo.dir/DefaultPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/DefaultPoller.o -MF CMakeFiles/cgmuduo.dir/DefaultPoller.o.d -o CMakeFiles/cgmuduo.dir/DefaultPoller.o -c /home/cgMuduo/DefaultPoller.cc

CMakeFiles/cgmuduo.dir/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/DefaultPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/DefaultPoller.cc > CMakeFiles/cgmuduo.dir/DefaultPoller.i

CMakeFiles/cgmuduo.dir/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/DefaultPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/DefaultPoller.cc -o CMakeFiles/cgmuduo.dir/DefaultPoller.s

CMakeFiles/cgmuduo.dir/EpollPoller.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/EpollPoller.o: ../EpollPoller.cc
CMakeFiles/cgmuduo.dir/EpollPoller.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cgmuduo.dir/EpollPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/EpollPoller.o -MF CMakeFiles/cgmuduo.dir/EpollPoller.o.d -o CMakeFiles/cgmuduo.dir/EpollPoller.o -c /home/cgMuduo/EpollPoller.cc

CMakeFiles/cgmuduo.dir/EpollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/EpollPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/EpollPoller.cc > CMakeFiles/cgmuduo.dir/EpollPoller.i

CMakeFiles/cgmuduo.dir/EpollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/EpollPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/EpollPoller.cc -o CMakeFiles/cgmuduo.dir/EpollPoller.s

CMakeFiles/cgmuduo.dir/EventLoop.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/EventLoop.o: ../EventLoop.cc
CMakeFiles/cgmuduo.dir/EventLoop.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/cgmuduo.dir/EventLoop.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/EventLoop.o -MF CMakeFiles/cgmuduo.dir/EventLoop.o.d -o CMakeFiles/cgmuduo.dir/EventLoop.o -c /home/cgMuduo/EventLoop.cc

CMakeFiles/cgmuduo.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/EventLoop.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/EventLoop.cc > CMakeFiles/cgmuduo.dir/EventLoop.i

CMakeFiles/cgmuduo.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/EventLoop.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/EventLoop.cc -o CMakeFiles/cgmuduo.dir/EventLoop.s

CMakeFiles/cgmuduo.dir/EventLoopThread.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/EventLoopThread.o: ../EventLoopThread.cc
CMakeFiles/cgmuduo.dir/EventLoopThread.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/cgmuduo.dir/EventLoopThread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/EventLoopThread.o -MF CMakeFiles/cgmuduo.dir/EventLoopThread.o.d -o CMakeFiles/cgmuduo.dir/EventLoopThread.o -c /home/cgMuduo/EventLoopThread.cc

CMakeFiles/cgmuduo.dir/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/EventLoopThread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/EventLoopThread.cc > CMakeFiles/cgmuduo.dir/EventLoopThread.i

CMakeFiles/cgmuduo.dir/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/EventLoopThread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/EventLoopThread.cc -o CMakeFiles/cgmuduo.dir/EventLoopThread.s

CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o: ../EventLoopThreadPool.cc
CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o -MF CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o.d -o CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o -c /home/cgMuduo/EventLoopThreadPool.cc

CMakeFiles/cgmuduo.dir/EventLoopThreadPool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/EventLoopThreadPool.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/EventLoopThreadPool.cc > CMakeFiles/cgmuduo.dir/EventLoopThreadPool.i

CMakeFiles/cgmuduo.dir/EventLoopThreadPool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/EventLoopThreadPool.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/EventLoopThreadPool.cc -o CMakeFiles/cgmuduo.dir/EventLoopThreadPool.s

CMakeFiles/cgmuduo.dir/InetAddress.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/InetAddress.o: ../InetAddress.cc
CMakeFiles/cgmuduo.dir/InetAddress.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/cgmuduo.dir/InetAddress.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/InetAddress.o -MF CMakeFiles/cgmuduo.dir/InetAddress.o.d -o CMakeFiles/cgmuduo.dir/InetAddress.o -c /home/cgMuduo/InetAddress.cc

CMakeFiles/cgmuduo.dir/InetAddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/InetAddress.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/InetAddress.cc > CMakeFiles/cgmuduo.dir/InetAddress.i

CMakeFiles/cgmuduo.dir/InetAddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/InetAddress.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/InetAddress.cc -o CMakeFiles/cgmuduo.dir/InetAddress.s

CMakeFiles/cgmuduo.dir/Logger.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Logger.o: ../Logger.cc
CMakeFiles/cgmuduo.dir/Logger.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/cgmuduo.dir/Logger.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Logger.o -MF CMakeFiles/cgmuduo.dir/Logger.o.d -o CMakeFiles/cgmuduo.dir/Logger.o -c /home/cgMuduo/Logger.cc

CMakeFiles/cgmuduo.dir/Logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Logger.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Logger.cc > CMakeFiles/cgmuduo.dir/Logger.i

CMakeFiles/cgmuduo.dir/Logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Logger.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Logger.cc -o CMakeFiles/cgmuduo.dir/Logger.s

CMakeFiles/cgmuduo.dir/Poller.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Poller.o: ../Poller.cc
CMakeFiles/cgmuduo.dir/Poller.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/cgmuduo.dir/Poller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Poller.o -MF CMakeFiles/cgmuduo.dir/Poller.o.d -o CMakeFiles/cgmuduo.dir/Poller.o -c /home/cgMuduo/Poller.cc

CMakeFiles/cgmuduo.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Poller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Poller.cc > CMakeFiles/cgmuduo.dir/Poller.i

CMakeFiles/cgmuduo.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Poller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Poller.cc -o CMakeFiles/cgmuduo.dir/Poller.s

CMakeFiles/cgmuduo.dir/Socket.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Socket.o: ../Socket.cc
CMakeFiles/cgmuduo.dir/Socket.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/cgmuduo.dir/Socket.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Socket.o -MF CMakeFiles/cgmuduo.dir/Socket.o.d -o CMakeFiles/cgmuduo.dir/Socket.o -c /home/cgMuduo/Socket.cc

CMakeFiles/cgmuduo.dir/Socket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Socket.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Socket.cc > CMakeFiles/cgmuduo.dir/Socket.i

CMakeFiles/cgmuduo.dir/Socket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Socket.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Socket.cc -o CMakeFiles/cgmuduo.dir/Socket.s

CMakeFiles/cgmuduo.dir/TcpConnection.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/TcpConnection.o: ../TcpConnection.cc
CMakeFiles/cgmuduo.dir/TcpConnection.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/cgmuduo.dir/TcpConnection.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/TcpConnection.o -MF CMakeFiles/cgmuduo.dir/TcpConnection.o.d -o CMakeFiles/cgmuduo.dir/TcpConnection.o -c /home/cgMuduo/TcpConnection.cc

CMakeFiles/cgmuduo.dir/TcpConnection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/TcpConnection.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/TcpConnection.cc > CMakeFiles/cgmuduo.dir/TcpConnection.i

CMakeFiles/cgmuduo.dir/TcpConnection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/TcpConnection.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/TcpConnection.cc -o CMakeFiles/cgmuduo.dir/TcpConnection.s

CMakeFiles/cgmuduo.dir/TcpServer.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/TcpServer.o: ../TcpServer.cc
CMakeFiles/cgmuduo.dir/TcpServer.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/cgmuduo.dir/TcpServer.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/TcpServer.o -MF CMakeFiles/cgmuduo.dir/TcpServer.o.d -o CMakeFiles/cgmuduo.dir/TcpServer.o -c /home/cgMuduo/TcpServer.cc

CMakeFiles/cgmuduo.dir/TcpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/TcpServer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/TcpServer.cc > CMakeFiles/cgmuduo.dir/TcpServer.i

CMakeFiles/cgmuduo.dir/TcpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/TcpServer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/TcpServer.cc -o CMakeFiles/cgmuduo.dir/TcpServer.s

CMakeFiles/cgmuduo.dir/Thread.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Thread.o: ../Thread.cc
CMakeFiles/cgmuduo.dir/Thread.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/cgmuduo.dir/Thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Thread.o -MF CMakeFiles/cgmuduo.dir/Thread.o.d -o CMakeFiles/cgmuduo.dir/Thread.o -c /home/cgMuduo/Thread.cc

CMakeFiles/cgmuduo.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Thread.cc > CMakeFiles/cgmuduo.dir/Thread.i

CMakeFiles/cgmuduo.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Thread.cc -o CMakeFiles/cgmuduo.dir/Thread.s

CMakeFiles/cgmuduo.dir/Timestamp.o: CMakeFiles/cgmuduo.dir/flags.make
CMakeFiles/cgmuduo.dir/Timestamp.o: ../Timestamp.cc
CMakeFiles/cgmuduo.dir/Timestamp.o: CMakeFiles/cgmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/cgmuduo.dir/Timestamp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cgmuduo.dir/Timestamp.o -MF CMakeFiles/cgmuduo.dir/Timestamp.o.d -o CMakeFiles/cgmuduo.dir/Timestamp.o -c /home/cgMuduo/Timestamp.cc

CMakeFiles/cgmuduo.dir/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgmuduo.dir/Timestamp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgMuduo/Timestamp.cc > CMakeFiles/cgmuduo.dir/Timestamp.i

CMakeFiles/cgmuduo.dir/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgmuduo.dir/Timestamp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgMuduo/Timestamp.cc -o CMakeFiles/cgmuduo.dir/Timestamp.s

# Object files for target cgmuduo
cgmuduo_OBJECTS = \
"CMakeFiles/cgmuduo.dir/Acceptor.o" \
"CMakeFiles/cgmuduo.dir/Buffer.o" \
"CMakeFiles/cgmuduo.dir/Channel.o" \
"CMakeFiles/cgmuduo.dir/CurrentThread.o" \
"CMakeFiles/cgmuduo.dir/DefaultPoller.o" \
"CMakeFiles/cgmuduo.dir/EpollPoller.o" \
"CMakeFiles/cgmuduo.dir/EventLoop.o" \
"CMakeFiles/cgmuduo.dir/EventLoopThread.o" \
"CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o" \
"CMakeFiles/cgmuduo.dir/InetAddress.o" \
"CMakeFiles/cgmuduo.dir/Logger.o" \
"CMakeFiles/cgmuduo.dir/Poller.o" \
"CMakeFiles/cgmuduo.dir/Socket.o" \
"CMakeFiles/cgmuduo.dir/TcpConnection.o" \
"CMakeFiles/cgmuduo.dir/TcpServer.o" \
"CMakeFiles/cgmuduo.dir/Thread.o" \
"CMakeFiles/cgmuduo.dir/Timestamp.o"

# External object files for target cgmuduo
cgmuduo_EXTERNAL_OBJECTS =

../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Acceptor.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Buffer.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Channel.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/CurrentThread.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/DefaultPoller.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/EpollPoller.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/EventLoop.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/EventLoopThread.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/EventLoopThreadPool.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/InetAddress.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Logger.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Poller.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Socket.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/TcpConnection.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/TcpServer.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Thread.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/Timestamp.o
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/build.make
../lib/libcgmuduo.so: CMakeFiles/cgmuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cgMuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX shared library ../lib/libcgmuduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cgmuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cgmuduo.dir/build: ../lib/libcgmuduo.so
.PHONY : CMakeFiles/cgmuduo.dir/build

CMakeFiles/cgmuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cgmuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cgmuduo.dir/clean

CMakeFiles/cgmuduo.dir/depend:
	cd /home/cgMuduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgMuduo /home/cgMuduo /home/cgMuduo/build /home/cgMuduo/build /home/cgMuduo/build/CMakeFiles/cgmuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cgmuduo.dir/depend


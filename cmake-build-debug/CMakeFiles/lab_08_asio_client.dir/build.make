# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/kirill/Documents/Clion/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kirill/Documents/Clion/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kirill/Documents/4_semestr/lab-08-asio-client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab_08_asio_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab_08_asio_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab_08_asio_client.dir/flags.make

CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o: CMakeFiles/lab_08_asio_client.dir/flags.make
CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o: ../sources/source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o -c /home/kirill/Documents/4_semestr/lab-08-asio-client/sources/source.cpp

CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/Documents/4_semestr/lab-08-asio-client/sources/source.cpp > CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.i

CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/Documents/4_semestr/lab-08-asio-client/sources/source.cpp -o CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.s

CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o: CMakeFiles/lab_08_asio_client.dir/flags.make
CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o: ../tests/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o -c /home/kirill/Documents/4_semestr/lab-08-asio-client/tests/test.cpp

CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/Documents/4_semestr/lab-08-asio-client/tests/test.cpp > CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.i

CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/Documents/4_semestr/lab-08-asio-client/tests/test.cpp -o CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.s

# Object files for target lab_08_asio_client
lab_08_asio_client_OBJECTS = \
"CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o" \
"CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o"

# External object files for target lab_08_asio_client
lab_08_asio_client_EXTERNAL_OBJECTS =

lab_08_asio_client: CMakeFiles/lab_08_asio_client.dir/sources/source.cpp.o
lab_08_asio_client: CMakeFiles/lab_08_asio_client.dir/tests/test.cpp.o
lab_08_asio_client: CMakeFiles/lab_08_asio_client.dir/build.make
lab_08_asio_client: CMakeFiles/lab_08_asio_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lab_08_asio_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab_08_asio_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab_08_asio_client.dir/build: lab_08_asio_client

.PHONY : CMakeFiles/lab_08_asio_client.dir/build

CMakeFiles/lab_08_asio_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab_08_asio_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab_08_asio_client.dir/clean

CMakeFiles/lab_08_asio_client.dir/depend:
	cd /home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kirill/Documents/4_semestr/lab-08-asio-client /home/kirill/Documents/4_semestr/lab-08-asio-client /home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug /home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug /home/kirill/Documents/4_semestr/lab-08-asio-client/cmake-build-debug/CMakeFiles/lab_08_asio_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab_08_asio_client.dir/depend


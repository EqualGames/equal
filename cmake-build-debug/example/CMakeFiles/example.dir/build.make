# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mathe\workspace\equal-games\equal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

# Include any dependencies generated for this target.
include example\CMakeFiles\example.dir\depend.make

# Include the progress variables for this target.
include example\CMakeFiles\example.dir\progress.make

# Include the compile flags for this target's objects.
include example\CMakeFiles\example.dir\flags.make

example\CMakeFiles\example.dir\main.cpp.obj: example\CMakeFiles\example.dir\flags.make
example\CMakeFiles\example.dir\main.cpp.obj: ..\example\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/example.dir/main.cpp.obj"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\example.dir\main.cpp.obj /FdCMakeFiles\example.dir\ /FS -c C:\Users\mathe\workspace\equal-games\equal\example\main.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

example\CMakeFiles\example.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/main.cpp.i"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe > CMakeFiles\example.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mathe\workspace\equal-games\equal\example\main.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

example\CMakeFiles\example.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/main.cpp.s"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\example.dir\main.cpp.s /c C:\Users\mathe\workspace\equal-games\equal\example\main.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

example\CMakeFiles\example.dir\scenes\DemoScene.cpp.obj: example\CMakeFiles\example.dir\flags.make
example\CMakeFiles\example.dir\scenes\DemoScene.cpp.obj: ..\example\scenes\DemoScene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/CMakeFiles/example.dir/scenes/DemoScene.cpp.obj"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\example.dir\scenes\DemoScene.cpp.obj /FdCMakeFiles\example.dir\ /FS -c C:\Users\mathe\workspace\equal-games\equal\example\scenes\DemoScene.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

example\CMakeFiles\example.dir\scenes\DemoScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/scenes/DemoScene.cpp.i"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe > CMakeFiles\example.dir\scenes\DemoScene.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mathe\workspace\equal-games\equal\example\scenes\DemoScene.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

example\CMakeFiles\example.dir\scenes\DemoScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/scenes/DemoScene.cpp.s"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\example.dir\scenes\DemoScene.cpp.s /c C:\Users\mathe\workspace\equal-games\equal\example\scenes\DemoScene.cpp
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

# Object files for target example
example_OBJECTS = \
"CMakeFiles\example.dir\main.cpp.obj" \
"CMakeFiles\example.dir\scenes\DemoScene.cpp.obj"

# External object files for target example
example_EXTERNAL_OBJECTS =

example\example.exe: example\CMakeFiles\example.dir\main.cpp.obj
example\example.exe: example\CMakeFiles\example.dir\scenes\DemoScene.cpp.obj
example\example.exe: example\CMakeFiles\example.dir\build.make
example\example.exe: equal\equal-s-d.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-network-d.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\ImGui-SFML.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-graphics-d.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-window-d.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-system-d.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\imguid.lib
example\example.exe: C:\bin\vcpkg\installed\x64-windows\debug\lib\pugixml_d.lib
example\example.exe: example\CMakeFiles\example.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable example.exe"
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	"C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\example.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\example.dir\objects1.rsp @<<
 /out:example.exe /implib:example.lib /pdb:C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example\example.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\mathe\workspace\equal-games\equal\equal\..\vendor\entt\src  ..\equal\equal-s-d.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-network-d.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\ImGui-SFML.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-graphics-d.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-window-d.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\sfml-system-d.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\imguid.lib opengl32.lib glu32.lib C:\bin\vcpkg\installed\x64-windows\debug\lib\pugixml_d.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	echo >nul && "C:\Program Files\PowerShell\7\pwsh.exe" -noprofile -executionpolicy Bypass -file C:/bin/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary C:/Users/mathe/workspace/equal-games/equal/cmake-build-debug/example/example.exe -installedDir C:/bin/vcpkg/installed/x64-windows/debug/bin -OutVariable out
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug

# Rule to build all files generated by this target.
example\CMakeFiles\example.dir\build: example\example.exe

.PHONY : example\CMakeFiles\example.dir\build

example\CMakeFiles\example.dir\clean:
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example
	$(CMAKE_COMMAND) -P CMakeFiles\example.dir\cmake_clean.cmake
	cd C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug
.PHONY : example\CMakeFiles\example.dir\clean

example\CMakeFiles\example.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\mathe\workspace\equal-games\equal C:\Users\mathe\workspace\equal-games\equal\example C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example C:\Users\mathe\workspace\equal-games\equal\cmake-build-debug\example\CMakeFiles\example.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : example\CMakeFiles\example.dir\depend


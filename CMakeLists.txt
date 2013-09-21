cmake_minimum_required (VERSION 2.8)
project (Twil)
include (FindPkgConfig)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set (standard "-stdlib=libc++ -std=c++11")
	set (math "-msse2")
	set (warning "-pedantic -Wall -Wextra -Wglobal-constructors -Wnon-virtual-dtor -Wshadow -Wnewline-eof -Wno-unused-parameter") #
	set (debug "-ggdb -fsanitize=address -fsanitize=undefined")
	set (release "-DNDEBUG -O3 -flto")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
	set (linker "-lc++abi")
	set (linker_symbol "-Wl,--gc-sections")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (standard "-std=c++11")
	set (math "-mfpmath=sse -msse2")
	set (warning "-pedantic -Wall -Wextra -Wnon-virtual-dtor -Wno-missing-field-initializers -Wno-unused-parameter")
	set (debug "-ggdb")
	set (release "-DNDEBUG -O3 -flto")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
	set (linker_symbol "-Wl,--gc-sections")
else ()
	message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

set (CMAKE_CXX_FLAGS "${standard} ${math} ${warning}")
set (CMAKE_CXX_FLAGS_DEBUG "${debug}")
set (CMAKE_CXX_FLAGS_RELEASE "${release} ${symbol}")
set (CMAKE_EXE_LINKER_FLAGS "${linker}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${linker_symbol}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${release} ${symbol} ${debug}")
set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${linker_symbol}")

find_package (Freetype REQUIRED)
find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	find_package (X11 REQUIRED)
	pkg_check_modules (XCBPKG x11-xcb xcb-keysyms x11-xcb REQUIRED)

	set (platform_search_path
		Twil/Linux
		${XCBPKG_INCLUDE_DIRS}
		${X11_INCLUDE_DIRS})

	set (platform_libs
		${CMAKE_DL_LIBS}
		${XCBPKG_LIBRARIES}
		${X11_LIBRARIES})
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

include_directories (
	Twil
	Twil/Header
	${platform_search_path}
	${FREETYPE_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS})

add_subdirectory (Twil)
add_subdirectory (Example)

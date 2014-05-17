cmake_minimum_required (VERSION 2.8)
project (Twil)
include (FindPkgConfig)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set (standard "-std=c++1y")
	set (math "-msse2")
	set (warning "-pedantic -Wall -Wextra -Wglobal-constructors -Wnon-virtual-dtor -Wshadow -Wnewline-eof -Wno-unused-parameter -Wno-unused-variable") #
	set (debug "-ggdb -fsanitize=address -fsanitize=undefined -fno-sanitize-recover")
	set (release "-DNDEBUG -O3 -flto")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
#	set (linker "-lc++abi")
	set (linker_symbol "-Wl,--gc-sections")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (standard "-std=c++1y")
	set (math "-mfpmath=sse -msse2")
	set (warning "-pedantic -Wall -Wextra -Wnon-virtual-dtor -Wno-missing-field-initializers -Wno-unused-parameter")
	set (debug "-ggdb")
	set (release "-DNDEBUG -O3 -flto -ffat-lto-objects")
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

include_directories (
	Twil
	Twil/${CMAKE_SYSTEM_NAME}
	Twil/Header
	${FREETYPE_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS})

add_subdirectory (Twil)
add_subdirectory (Example)

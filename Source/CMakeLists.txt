cmake_minimum_required (VERSION 2.8)
project (Twil)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set (standard "-stdlib=libc++ -std=c++11")
	set (math "-msse2") # -ffast-math
	set (warning "-pedantic -Wall -Wextra -Wglobal-constructors -Wnon-virtual-dtor -Wshadow -Wnewline-eof -Wno-unused-parameter") # -Wsign-conversion
	set (debug "-ggdb")
	set (release "-DNDEBUG -O3 -flto")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
	set (linker_symbol "-Wl,--gc-sections")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (standard "-std=c++11")
	set (math "-mfpmath=sse -msse2 -ffast-math")
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
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${linker_symbol}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${release} ${symbol} ${debug}")
set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${linker_symbol}")

set (fonts
	Font/DejaVuSans.ttf
	Font/DejaVuSans-Bold.ttf
	Font/DejaVuSansMono.ttf
)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	find_package (X11 REQUIRED)

	set (platform_sources
		Linux/Platform/Key.cpp
		Linux/Platform/Application.cpp
		Linux/Platform/Glx.cpp
		Linux/Platform/SymbolLoader.cpp
		Linux/Platform/Window.cpp
	)

	set (platform_search_path
		Linux
		${X11_INCLUDE_DIRS}
	)

	set (platform_libs
		dl
		xcb
		X11-xcb
		${X11_LIBRARIES}
	)
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

set (sources
	Attribute/Color1f.cpp
	Attribute/Color4b.cpp
	Attribute/Offset1i.cpp
	Attribute/Position2f.cpp
	Attribute/Position2h.cpp
	Attribute/Size2h.cpp
	Attribute/Texcoord1f.cpp
	Attribute/Texcoord2h.cpp
	Ft/Bitmap.cpp
	Ft/Face.cpp
	Ft/Library.cpp
	Ft/Outline.cpp
	Ft/Size.cpp
	Ft/Stroker.cpp
	Gl/Buffer.cpp
	Gl/Context.cpp
	Gl/Program.cpp
	Gl/Shader.cpp
	Gl/Texture.cpp
	Gl/VertexArray.cpp
	Loader/Png.cpp
	Program/FillSolid.cpp
	Program/OutlineGradient.cpp
	Theme/Button.cpp
	Theme/Drawable.cpp
	Theme/Label.cpp
	Theme/Manager.cpp
	Theme/Settings.cpp
	Theme/StreamArray.cpp
	Theme/TextureArray.cpp
	Ui/Application.cpp
	Ui/Margin.cpp
	Ui/Button.cpp
	Ui/Event.cpp
	Ui/Container.cpp
	Ui/Centered.cpp
	Ui/PartitionBox.cpp
	Ui/KeyboardHandler.cpp
	Ui/Label.cpp
	Ui/MouseHandler.cpp
	Ui/SplitBox.cpp
	Ui/Tuple.cpp
	Ui/WindowBase.cpp
	Ui/Widget.cpp
	Ui/Window.cpp
	Vertex/FillSolid.cpp
	Vertex/OutlineGradient.cpp
	${platform_sources}
)

set (shaders
	Shader/FillSolid.frag
	Shader/FillSolid.geom
	Shader/FillSolid.vert
	Shader/OutlineGradient.frag
	Shader/OutlineGradient.geom
	Shader/OutlineGradient.vert
)

add_executable (hello
	Hello.cpp
	${sources}
	${shaders}
)

find_package (Freetype REQUIRED)
find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)

include_directories (
	.
	Header
	${platform_search_path}
	${FREETYPE_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS}
)

target_link_libraries (hello
	${platform_libs}
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES}
)

install (FILES ${fonts} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Font)
install (FILES ${shaders} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Shader)

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

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	set (platform_sources
		Linux/Platform/Key.cpp
		Linux/Platform/Key.hpp
		Linux/Platform/Application.cpp
		Linux/Platform/Application.hpp
		Linux/Platform/Glx.cpp
		Linux/Platform/Glx.hpp
		Linux/Platform/SymbolLoader.cpp
		Linux/Platform/SymbolLoader.hpp
		Linux/Platform/Window.cpp
		Linux/Platform/Window.hpp
	)

	source_group(Platform FILES ${platform_sources})

	find_package (X11 REQUIRED)

	set (platform_search_path
		Linux
		${X11_INCLUDE_DIRS}
	)

	set (platform_libs
		dl
		xcb
		xcb-keysyms
		X11-xcb
		${X11_LIBRARIES}
	)
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

set (attribute_sources
	Attribute/Color4b.cpp
	Attribute/Color4b.hpp
	Attribute/Offset1i.cpp
	Attribute/Offset1i.hpp
	Attribute/Position2h.cpp
	Attribute/Position2h.hpp
	Attribute/Size2h.cpp
	Attribute/Size2h.hpp
	Attribute/Texcoord2h.cpp
	Attribute/Texcoord2h.hpp
)

source_group(Attribute FILES ${attribute_sources})

set (data_sources
	Data/Memory.cpp
	Data/Memory.hpp
	Data/Rope.cpp
	Data/Rope.hpp
	Data/Tuple.cpp
	Data/Tuple.hpp
)
source_group(Data FILES ${data_sources})

set (ft_sources
	Ft/Bitmap.cpp
	Ft/Bitmap.hpp
	Ft/Face.cpp
	Ft/Face.hpp
	Ft/Library.cpp
	Ft/Library.hpp
	Ft/Outline.cpp
	Ft/Outline.hpp
	Ft/Size.cpp
	Ft/Size.hpp
	Ft/Stroker.cpp
	Ft/Stroker.hpp
)

source_group(Ft FILES ${ft_sources})

set (gl_sources
	Gl/Buffer.cpp
	Gl/Buffer.hpp
	Gl/Context.cpp
	Gl/Context.hpp
	Gl/Program.cpp
	Gl/Program.hpp
	Gl/Shader.cpp
	Gl/Shader.hpp
	Gl/Texture.cpp
	Gl/Texture.hpp
	Gl/VertexArray.cpp
	Gl/VertexArray.hpp
)

source_group(Gl FILES ${gl_sources})

set (loader_sources
	Loader/Png.cpp
	Loader/Png.hpp
)

source_group(Loader FILES ${loader_sources})

set (program_sources
	Program/Bitmap.cpp
	Program/Bitmap.hpp
	Program/FillSolid.cpp
	Program/FillSolid.hpp
	Program/OutlineGradient.cpp
	Program/OutlineGradient.hpp
)

source_group(Program FILES ${program_sources})

set (shader_sources
	Shader/Bitmap.frag
	Shader/Bitmap.geom
	Shader/Bitmap.vert
	Shader/FillSolid.frag
	Shader/FillSolid.geom
	Shader/FillSolid.vert
	Shader/OutlineGradient.frag
	Shader/OutlineGradient.geom
	Shader/OutlineGradient.vert
)

source_group(Shader FILES ${shader_sources})

set (theme_sources
	Theme/Button.cpp
	Theme/Button.hpp
	Theme/Drawable.cpp
	Theme/Drawable.hpp
	Theme/Image.cpp
	Theme/Image.hpp
	Theme/Label.cpp
	Theme/Label.hpp
	Theme/Manager.cpp
	Theme/Manager.hpp
	Theme/Settings.cpp
	Theme/Settings.hpp
	Theme/StreamArray.cpp
	Theme/StreamArray.hpp
	Theme/TextureArray.cpp
	Theme/TextureArray.hpp
)

source_group(Theme FILES ${theme_sources})

set (ui_sources
	Ui/Application.cpp
	Ui/Application.hpp
	Ui/Margin.cpp
	Ui/Margin.hpp
	Ui/Button.cpp
	Ui/Button.hpp
	Ui/Event.cpp
	Ui/Event.hpp
	Ui/Container.cpp
	Ui/Container.hpp
	Ui/Centered.cpp
	Ui/Centered.hpp
	Ui/Image.cpp
	Ui/Image.hpp
	Ui/KeyboardHandler.cpp
	Ui/KeyboardHandler.hpp
	Ui/KeyboardManager.cpp
	Ui/KeyboardManager.hpp
	Ui/Label.cpp
	Ui/Label.hpp
	Ui/MouseHandler.cpp
	Ui/MouseHandler.hpp
	Ui/MouseManager.cpp
	Ui/MouseManager.hpp
	Ui/PartitionBox.cpp
	Ui/PartitionBox.hpp
	Ui/SplitBox.cpp
	Ui/SplitBox.hpp
	Ui/Widget.cpp
	Ui/Widget.hpp
	Ui/Window.cpp
	Ui/Window.hpp
	Ui/WindowBase.cpp
	Ui/WindowBase.hpp
)

source_group(Ui FILES ${ui_sources})

set (vertex_sources
	Vertex/Bitmap.cpp
	Vertex/Bitmap.hpp
	Vertex/FillSolid.cpp
	Vertex/FillSolid.hpp
	Vertex/OutlineGradient.cpp
	Vertex/OutlineGradient.hpp
)

source_group(Vertex FILES ${vertex_sources})

add_executable (hello
	Hello.cpp
	${attribute_sources}
	${data_sources}
	${ft_sources}
	${gl_sources}
	${loader_sources}
	${platform_sources}
	${program_sources}
	${shader_sources}
	${theme_sources}
	${ui_sources}
	${vertex_sources}
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

set (fonts
	Font/DejaVuSans.ttf
	Font/DejaVuSans-Bold.ttf
	Font/DejaVuSansMono.ttf
)

install (FILES ${fonts} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Font)
install (FILES ${shader_sources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Shader)

cmake_minimum_required (VERSION 2.8)
project (Twil)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set (standard "-stdlib=libc++ -std=c++11")
	set (math "-msse2") # -ffast-math
	set (warning "-pedantic -Wall -Wextra -Wglobal-constructors -Wnon-virtual-dtor -Wshadow -Wnewline-eof") # -Wsign-conversion
	set (debug "-ggdb")
	set (debug_runtime "-fsanitize=bounds -fsanitize=undefined")
	set (release "-DNDEBUG -O4")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
	set (linker_symbol "-Wl,--gc-sections")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (standard "-std=c++11")
	set (math "-mfpmath=sse -msse2 -ffast-math")
	set (warning "-pedantic -Wall -Wextra -Wnon-virtual-dtor -Wshadow") # -Wsign-conversion
	set (debug "-ggdb")
	set (debug_runtime)
	set (release "-DNDEBUG -O3 -flto")
	set (symbol "-fno-rtti -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
	set (linker_symbol "-Wl,--gc-sections")
else ()
	message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

set (CMAKE_CXX_FLAGS "${standard} ${math} ${warning}")
set (CMAKE_CXX_FLAGS_DEBUG "${debug} ${debug_runtime}")
set (CMAKE_CXX_FLAGS_RELEASE "${release} ${symbol}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${linker_symbol}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${release} ${symbol} ${debug}")
set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${linker_symbol}")

set (fonts
	Font/DejaVuSans.ttf
	Font/DejaVuSans-Bold.ttf
	Font/DejaVuSansMono.ttf
)

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
	Gl/StreamArray.cpp
	Gl/Texture.cpp
	Gl/TextureArray.cpp
	Gl/VertexArray.cpp
	Loader/Png.cpp
	Math/BarycentricInterpolator.cpp
	Math/Matrix2.cpp
	Math/Matrix3.cpp
	Math/Matrix4.cpp
	Math/Vector2.cpp
	Math/Vector3.cpp
	Math/Vector4.cpp
	${CMAKE_SYSTEM_NAME}/Platform/Key.cpp
	${CMAKE_SYSTEM_NAME}/Platform/Application.cpp
	${CMAKE_SYSTEM_NAME}/Platform/SymbolLoader.cpp
	${CMAKE_SYSTEM_NAME}/Platform/Window.cpp
	Program/FillSolid.cpp
	Program/OutlineGradient.cpp
	Theme/Button.cpp
	Theme/Label.cpp
	Theme/Manager.cpp
	Ui/Application.cpp
	Ui/Button.cpp
	Ui/Event.cpp
	Ui/Centered.cpp
	Ui/Drawable.cpp
	Ui/DrawableContainer.cpp
	Ui/PartitionBox.cpp
	Ui/KeyboardHandler.cpp
	Ui/Label.cpp
	Ui/MouseHandler.cpp
	Ui/Spacer.cpp
	Ui/SplitBox.cpp
	Ui/Tuple.cpp
	Ui/WindowBase.cpp
	Ui/Widget.cpp
	Ui/WidgetContainer.cpp
	Ui/Window.cpp
	Vertex/FillSolid.cpp
	Vertex/OutlineGradient.cpp
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
find_package (OpenAL REQUIRED)
find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)

include_directories (
	.
	Common
	Header
	${CMAKE_SYSTEM_NAME}
	${FREETYPE_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS}
)

target_link_libraries (hello
	-lc++abi
	${FREETYPE_LIBRARIES}
	${OPENAL_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES}
)

install (FILES ${fonts} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Font)
install (FILES ${shaders} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Shader)

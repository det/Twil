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
		Linux/Platform/Window.hpp)

	source_group(Platform FILES ${platform_sources})
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
	Attribute/Texcoord2h.hpp)

source_group(Attribute FILES ${attribute_sources})

set (data_sources
	Data/Event.cpp
	Data/Event.hpp
	Data/Memory.cpp
	Data/Memory.hpp
	Data/Rope.cpp
	Data/Rope.hpp
	Data/Tuple.cpp
	Data/Tuple.hpp)

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
	Ft/Stroker.hpp)

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
	Gl/VertexArray.hpp)

source_group(Gl FILES ${gl_sources})

set (loader_sources
	Loader/Png.cpp
	Loader/Png.hpp)

source_group(Loader FILES ${loader_sources})

set (program_sources
	Program/Bitmap.cpp
	Program/Bitmap.hpp
	Program/FillSolid.cpp
	Program/FillSolid.hpp
	Program/OutlineGradient.cpp
	Program/OutlineGradient.hpp)

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
	Shader/OutlineGradient.vert)

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
	Theme/TextureArray.hpp)

source_group(Theme FILES ${theme_sources})

set (ui_sources
	Ui/Application.cpp
	Ui/Application.hpp
	Ui/Margin.cpp
	Ui/Margin.hpp
	Ui/Button.cpp
	Ui/Button.hpp
	Ui/Container.cpp
	Ui/Container.hpp
	Ui/Centered.cpp
	Ui/Centered.hpp
	Ui/Grid.cpp
	Ui/Grid.hpp
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
	Ui/WidgetAdaptor.cpp
	Ui/WidgetAdaptor.hpp
	Ui/Window.cpp
	Ui/Window.hpp
	Ui/WindowBase.cpp
	Ui/WindowBase.hpp)

source_group(Ui FILES ${ui_sources})

set (vertex_sources
	Vertex/Bitmap.cpp
	Vertex/Bitmap.hpp
	Vertex/FillSolid.cpp
	Vertex/FillSolid.hpp
	Vertex/OutlineGradient.cpp
	Vertex/OutlineGradient.hpp)

source_group(Vertex FILES ${vertex_sources})

add_library (Twil
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
	${vertex_sources})

target_link_libraries (Twil
	${platform_libs}
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES})

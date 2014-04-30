if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	set (platform_sources
		Linux/Platform/Key.cpp
		Linux/Platform/Key.hpp
		Linux/Platform/KeyFwd.hpp
		Linux/Platform/Application.cpp
		Linux/Platform/Application.hpp
		Linux/Platform/ApplicationFwd.hpp
		Linux/Platform/Glx.cpp
		Linux/Platform/Glx.hpp
		Linux/Platform/GlxFwd.hpp
		Linux/Platform/SymbolLoader.cpp
		Linux/Platform/SymbolLoader.hpp
		Linux/Platform/SymbolLoaderFwd.hpp
		Linux/Platform/Window.cpp
		Linux/Platform/Window.hpp
		Linux/Platform/WindowFwd.hpp
		Linux/Platform/X11.cpp
		Linux/Platform/X11.hpp
		Linux/Platform/X11Fwd.hpp)

	source_group(Platform FILES ${platform_sources})

	set (platform_libraries ${X11_LIBRARIES})
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

set (attribute_sources
	Attribute/Color4b.cpp
	Attribute/Color4b.hpp
	Attribute/Color4bFwd.hpp
	Attribute/Offset1i.cpp
	Attribute/Offset1i.hpp
	Attribute/Offset1iFwd.hpp
	Attribute/Position2h.cpp
	Attribute/Position2h.hpp
	Attribute/Position2hFwd.hpp
	Attribute/Size2h.cpp
	Attribute/Size2h.hpp
	Attribute/Size2hFwd.hpp
	Attribute/Texcoord2h.cpp
	Attribute/Texcoord2h.hpp
	Attribute/Texcoord2hFwd.hpp)

source_group(Attribute FILES ${attribute_sources})

set (data_sources
	Data/Event.cpp
	Data/Event.hpp
	Data/EventFwd.hpp
	Data/Memory.cpp
	Data/Memory.hpp
	Data/MemoryFwd.hpp
	Data/Rope.cpp
	Data/Rope.hpp
	Data/RopeFwd.hpp
	Data/ScopeGuard.cpp
	Data/ScopeGuard.hpp
	Data/ScopeGuardFwd.hpp
	Data/Tuple.cpp
	Data/Tuple.hpp
	Data/TupleFwd.hpp)

source_group(Data FILES ${data_sources})

set (ft_sources
	Ft/Bitmap.cpp
	Ft/Bitmap.hpp
	Ft/BitmapFwd.hpp
	Ft/Face.cpp
	Ft/Face.hpp
	Ft/FaceFwd.hpp
	Ft/Library.cpp
	Ft/Library.hpp
	Ft/LibraryFwd.hpp
	Ft/Outline.cpp
	Ft/Outline.hpp
	Ft/OutlineFwd.hpp
	Ft/Size.cpp
	Ft/Size.hpp
	Ft/SizeFwd.hpp
	Ft/Stroker.cpp
	Ft/Stroker.hpp
	Ft/StrokerFwd.hpp)

source_group(Ft FILES ${ft_sources})

set (gl_sources
	Gl/Buffer.cpp
	Gl/Buffer.hpp
	Gl/BufferFwd.hpp
	Gl/Context.cpp
	Gl/Context.hpp
	Gl/ContextFwd.hpp
	Gl/Program.cpp
	Gl/Program.hpp
	Gl/ProgramFwd.hpp
	Gl/Shader.cpp
	Gl/Shader.hpp
	Gl/ShaderFwd.hpp
	Gl/Texture.cpp
	Gl/Texture.hpp
	Gl/TextureFwd.hpp
	Gl/VertexArray.cpp
	Gl/VertexArray.hpp
	Gl/VertexArrayFwd.hpp)

source_group(Gl FILES ${gl_sources})

set (loader_sources
	Loader/Png.cpp
	Loader/Png.hpp
	Loader/PngFwd.hpp)


source_group(Loader FILES ${loader_sources})

set (program_sources
	Program/Bitmap.cpp
	Program/Bitmap.hpp
	Program/BitmapFwd.hpp
	Program/FillSolid.cpp
	Program/FillSolid.hpp
	Program/FillSolidFwd.hpp
	Program/OutlineGradient.cpp
	Program/OutlineGradient.hpp
	Program/OutlineGradientFwd.hpp)

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
	Theme/ButtonFwd.hpp
	Theme/Drawable.cpp
	Theme/Drawable.hpp
	Theme/DrawableFwd.hpp
	Theme/Image.cpp
	Theme/Image.hpp
	Theme/ImageFwd.hpp
	Theme/Label.cpp
	Theme/Label.hpp
	Theme/LabelFwd.hpp
	Theme/Manager.cpp
	Theme/Manager.hpp
	Theme/ManagerFwd.hpp
	Theme/Settings.cpp
	Theme/Settings.hpp
	Theme/SettingsFwd.hpp
	Theme/StreamArray.cpp
	Theme/StreamArray.hpp
	Theme/StreamArrayFwd.hpp
	Theme/TextureArray.cpp
	Theme/TextureArray.hpp
	Theme/TextureArrayFwd.hpp)

source_group(Theme FILES ${theme_sources})

set (ui_sources
	Ui/Application.cpp
	Ui/Application.hpp
	Ui/ApplicationFwd.hpp
	Ui/Margin.cpp
	Ui/Margin.hpp
	Ui/MarginFwd.hpp
	Ui/Button.cpp
	Ui/Button.hpp
	Ui/ButtonFwd.hpp
	Ui/Container.cpp
	Ui/Container.hpp
	Ui/ContainerFwd.hpp
	Ui/Centered.cpp
	Ui/Centered.hpp
	Ui/CenteredFwd.hpp
	Ui/Grid.cpp
	Ui/Grid.hpp
	Ui/GridFwd.hpp
	Ui/Image.cpp
	Ui/Image.hpp
	Ui/ImageFwd.hpp
	Ui/KeyboardHandler.cpp
	Ui/KeyboardHandler.hpp
	Ui/KeyboardHandlerFwd.hpp
	Ui/Label.cpp
	Ui/Label.hpp
	Ui/LabelFwd.hpp
	Ui/MouseHandler.cpp
	Ui/MouseHandler.hpp
	Ui/MouseHandlerFwd.hpp
	Ui/PartitionBox.cpp
	Ui/PartitionBox.hpp
	Ui/PartitionBoxFwd.hpp
	Ui/SplitBox.cpp
	Ui/SplitBox.hpp
	Ui/SplitBoxFwd.hpp
	Ui/Widget.cpp
	Ui/Widget.hpp
	Ui/WidgetFwd.hpp
	Ui/Window.cpp
	Ui/Window.hpp
	Ui/WindowFwd.hpp
	Ui/WindowBase.cpp
	Ui/WindowBase.hpp
	Ui/WindowBaseFwd.hpp
	Ui/WindowHandler.cpp
	Ui/WindowHandler.hpp
	Ui/WindowHandlerFwd.hpp)

source_group(Ui FILES ${ui_sources})

set (vertex_sources
	Vertex/Bitmap.cpp
	Vertex/Bitmap.hpp
	Vertex/BitmapFwd.hpp
	Vertex/FillSolid.cpp
	Vertex/FillSolid.hpp
	Vertex/FillSolidFwd.hpp
	Vertex/OutlineGradient.cpp
	Vertex/OutlineGradient.hpp
	Vertex/OutlineGradientFwd.hpp)

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
	${platform_libraries}
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES})

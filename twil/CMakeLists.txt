if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	set (platform_sources
		linux/platform/key.cpp
		linux/platform/key.hpp
		linux/platform/key.hxx
		linux/platform/application.cpp
		linux/platform/application.hpp
		linux/platform/application.hxx
		linux/platform/glx.cpp
		linux/platform/glx.hpp
		linux/platform/glx.hxx
		linux/platform/symbol_loader.cpp
		linux/platform/symbol_loader.hpp
		linux/platform/symbol_loader.hxx
		linux/platform/window.cpp
		linux/platform/window.hpp
		linux/platform/window.hxx
		linux/platform/x11.cpp
		linux/platform/x11.hpp
		linux/platform/x11.hxx)

	source_group(platform FILES ${platform_sources})

	set (platform_libraries ${X11_LIBRARIES} Xrandr)
else ()
	message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

set (attribute_sources
	attribute/color4b.cpp
	attribute/color4b.hpp
	attribute/color4b.hxx
	attribute/color4h.cpp
	attribute/color4h.hpp
	attribute/color4h.hxx
	attribute/offset1i.cpp
	attribute/offset1i.hpp
	attribute/offset1i.hxx
	attribute/position2h.cpp
	attribute/position2h.hpp
	attribute/position2h.hxx
	attribute/size2h.cpp
	attribute/size2h.hpp
	attribute/size2h.hxx
	attribute/texcoord2h.cpp
	attribute/texcoord2h.hpp
	attribute/texcoord2h.hxx)

source_group(attribute FILES ${attribute_sources})

set (data_sources
	data/event.cpp
	data/event.hpp
	data/event.hxx
	data/scope_guard.cpp
	data/scope_guard.hpp
	data/scope_guard.hxx
	data/tuple.cpp
	data/tuple.hpp
	data/tuple.hxx)

source_group(data FILES ${data_sources})

set (ft_sources
	ft/bitmap.cpp
	ft/bitmap.hpp
	ft/bitmap.hxx
	ft/face.cpp
	ft/face.hpp
	ft/face.hxx
	ft/library.cpp
	ft/library.hpp
	ft/library.hxx
	ft/outline.cpp
	ft/outline.hpp
	ft/outline.hxx
	ft/size.cpp
	ft/size.hpp
	ft/size.hxx
	ft/stroker.cpp
	ft/stroker.hpp
	ft/stroker.hxx)

source_group(ft FILES ${ft_sources})

set (gl_sources
	gl/buffer.cpp
	gl/buffer.hpp
	gl/buffer.hxx
	gl/context.cpp
	gl/context.hpp
	gl/context.hxx
	gl/program.cpp
	gl/program.hpp
	gl/program.hxx
	gl/shader.cpp
	gl/shader.hpp
	gl/shader.hxx
	gl/texture.cpp
	gl/texture.hpp
	gl/texture.hxx
	gl/vertex_array.cpp
	gl/vertex_array.hpp
	gl/vertex_array.hxx)

source_group(gl FILES ${gl_sources})

set (loader_sources
	loader/png.cpp
	loader/png.hpp
	loader/png.hxx)


source_group(loader FILES ${loader_sources})

set (program_sources
	program/bitmap.cpp
	program/bitmap.hpp
	program/bitmap.hxx
	program/fill_solid.cpp
	program/fill_solid.hpp
	program/fill_solid.hxx
	program/outline_gradient.cpp
	program/outline_gradient.hpp
	program/outline_gradient.hxx)

source_group(program FILES ${program_sources})

set (shader_sources
	shader/bitmap.frag
	shader/bitmap.geom
	shader/bitmap.vert
	shader/fill_solid.frag
	shader/fill_solid.geom
	shader/fill_solid.vert
	shader/outline_gradient.frag
	shader/outline_gradient.geom
	shader/outline_gradient.vert)

source_group(shader FILES ${shader_sources})

set (theme_sources
	theme/button.cpp
	theme/button.hpp
	theme/button.hxx
	theme/drawable.cpp
	theme/drawable.hpp
	theme/drawable.hxx
	theme/image.cpp
	theme/image.hpp
	theme/image.hxx
	theme/label.cpp
	theme/label.hpp
	theme/label.hxx
	theme/manager.cpp
	theme/manager.hpp
	theme/manager.hxx
	theme/scaling.cpp
	theme/scaling.hpp
	theme/scaling.hxx
	theme/settings.cpp
	theme/settings.hpp
	theme/settings.hxx
	theme/stream_array.cpp
	theme/stream_array.hpp
	theme/stream_array.hxx
	theme/texture_array.cpp
	theme/texture_array.hpp
	theme/texture_array.hxx)

source_group(theme FILES ${theme_sources})

set (ui_sources
	ui/application.cpp
	ui/application.hpp
	ui/application.hxx
	ui/margin.cpp
	ui/margin.hpp
	ui/margin.hxx
	ui/button.cpp
	ui/button.hpp
	ui/button.hxx
	ui/container.cpp
	ui/container.hpp
	ui/container.hxx
	ui/centered.cpp
	ui/centered.hpp
	ui/centered.hxx
	ui/grid.cpp
	ui/grid.hpp
	ui/grid.hxx
	ui/image.cpp
	ui/image.hpp
	ui/image.hxx
	ui/keyboard_handler.cpp
	ui/keyboard_handler.hpp
	ui/keyboard_handler.hxx
	ui/label.cpp
	ui/label.hpp
	ui/label.hxx
	ui/mouse_handler.cpp
	ui/mouse_handler.hpp
	ui/mouse_handler.hxx
	ui/partition_box.cpp
	ui/partition_box.hpp
	ui/partition_box.hxx
	ui/split_box.cpp
	ui/split_box.hpp
	ui/split_box.hxx
	ui/unit.cpp
	ui/unit.hpp
	ui/unit.hxx
	ui/widget.cpp
	ui/widget.hpp
	ui/widget.hxx
	ui/window.cpp
	ui/window.hpp
	ui/window.hxx
	ui/window_base.cpp
	ui/window_base.hpp
	ui/window_base.hxx
	ui/window_handler.cpp
	ui/window_handler.hpp
	ui/window_handler.hxx)

source_group(ui FILES ${ui_sources})

set (vertex_sources
	vertex/bitmap.cpp
	vertex/bitmap.hpp
	vertex/bitmap.hxx
	vertex/fill_solid.cpp
	vertex/fill_solid.hpp
	vertex/fill_solid.hxx
	vertex/outline_gradient.cpp
	vertex/outline_gradient.hpp
	vertex/outline_gradient.hxx)

source_group(vertex FILES ${vertex_sources})

add_library (twil
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

target_link_libraries (twil
	${platform_libraries}
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${PNG_LIBRARIES})

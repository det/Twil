#include "Window.hpp"

#include "Application.hpp"
#include "Glx.hpp"
#include "SymbolLoader.hpp"
#include "Data/Memory.hpp"
#include "Gl/Context.hpp"

#include <cstring>
#include <cstdint>
#include <stdexcept>

#include <xcb/xcb_atom.h>

namespace {

struct XDeleterT
{
	template<typename T>
	void operator()(T * Object)
	{
		XFree(Object);
	}
};

}

namespace Twil {
namespace Platform {

WindowT::WindowT(ApplicationT & Application)
:
	mApplication{&Application}
{
	auto Display = static_cast< ::Display *>(mApplication->mDisplay);
	SymbolLoaderT Loader;
	Glx::initialize(Loader);

	static int VisualAttributes[] = {
		GLX_X_RENDERABLE ,					True,
		GLX_DRAWABLE_TYPE,					GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,					GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,					GLX_TRUE_COLOR,
		GLX_RED_SIZE,						8,
		GLX_GREEN_SIZE,						8,
		GLX_BLUE_SIZE,						8,
		GLX_ALPHA_SIZE,						8,
		GLX_DOUBLEBUFFER,					True,
		GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB,	True,
		None};

	int FramebufferCount;
	auto XScreen = DefaultScreen(Display);

	std::unique_ptr<GLXFBConfig[], XDeleterT> Configs{
		glXChooseFBConfig(
			Display,
			XScreen,
			VisualAttributes,
			&FramebufferCount)};

	if (Configs == nullptr)
	{
		throw std::runtime_error{"Unable to find matching video mode"};
	}

	auto & Config = Configs[0];
	int VisualId = 0;
	glXGetFBConfigAttrib(Display, Config, GLX_VISUAL_ID , &VisualId);

	auto Colormap = xcb_generate_id(mApplication->mConnection);
	mId = xcb_generate_id(mApplication->mConnection);

	// Find XCB screen
	auto Setup = xcb_get_setup(mApplication->mConnection);
	auto ScreenIter = xcb_setup_roots_iterator(Setup);
	int ScreenNum = XScreen;
	if (ScreenIter.rem > 0 && ScreenNum > 0)
	{
		--ScreenNum;
		xcb_screen_next(&ScreenIter);
	}
	auto Screen = ScreenIter.data;

	xcb_create_colormap(
		mApplication->mConnection,
		XCB_COLORMAP_ALLOC_NONE,
		Colormap,
		Screen->root,
		VisualId);

	uint32_t EventMask =
		XCB_EVENT_MASK_ENTER_WINDOW |
		XCB_EVENT_MASK_LEAVE_WINDOW |
		XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_BUTTON_PRESS |
		XCB_EVENT_MASK_BUTTON_RELEASE |
		XCB_EVENT_MASK_KEY_PRESS |
		XCB_EVENT_MASK_KEY_RELEASE |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY |
		XCB_EVENT_MASK_EXPOSURE;

	uint32_t ValueList[] = {0, EventMask, Colormap, XCB_NONE};
	uint32_t ValueMask = XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

	xcb_create_window(
		mApplication->mConnection,
		XCB_COPY_FROM_PARENT,
		mId,
		Screen->root,
		0, 0,
		320, 240,
		0,
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		VisualId,
		ValueMask,
		ValueList);

	if (mId == 0) throw std::runtime_error{"Unable to create window"};

	int ContextAttribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 3,
		None};

	mContext = glXCreateContextAttribsARB(Display, Config, 0, True, ContextAttribs);
	if (mContext == 0) throw std::runtime_error{"Unable to create OpenGL context"};

	Gl::Context::initialize(Loader);

	xcb_atom_t AtomList[] = {mApplication->mWmDeleteWindowAtom};

	xcb_change_property(
		mApplication->mConnection, XCB_PROP_MODE_REPLACE, mId,
		mApplication->mWmProtocolsAtom, mApplication->mAtomAtom, 32, 1, AtomList);

	xcb_map_window(mApplication->mConnection, mId);
	makeCurrent();
}

WindowT::~WindowT() noexcept
{
	auto Display = static_cast< ::Display *>(mApplication->mDisplay);
	auto Context = static_cast<GLXContext>(mContext);
	glXDestroyContext(Display, Context);
	xcb_destroy_window(mApplication->mConnection, mId);
}

void WindowT::makeCurrent()
{
	auto Display = static_cast< ::Display *>(mApplication->mDisplay);
	auto Context = static_cast<GLXContext>(mContext);
	glXMakeCurrent(Display, mId, Context);
}

void WindowT::swapBuffers()
{
	auto Display = static_cast< ::Display *>(mApplication->mDisplay);
	glXSwapBuffers(Display, mId);
}

void WindowT::setFullscreen(bool isFullscreen)
{
	xcb_client_message_event_t Message;
	Message.response_type = XCB_CLIENT_MESSAGE;
	Message.window = mId;
	Message.type = mApplication->mNetWmStateAtom;
	Message.format = 32;
	Message.data.data32[0] = isFullscreen ? 1 : 0;
	Message.data.data32[1] = mApplication->mNetWmStateFullscreenAtom;
	Message.data.data32[2] = 0;
	auto Pointer = reinterpret_cast<char const *>(&Message);
	xcb_send_event(mApplication->mConnection, 0, mId, XCB_EVENT_MASK_STRUCTURE_NOTIFY, Pointer);
	xcb_flush(mApplication->mConnection);
}

void WindowT::show()
{
	xcb_map_window(mApplication->mConnection, mId);
}

void WindowT::hide()
{
	xcb_unmap_window(mApplication->mConnection, mId);
}

void WindowT::resize(std::uint16_t Width, std::uint16_t Height)
{
	uint16_t Mask = XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT;
	uint32_t ValueList[] = {Width, Height, XCB_NONE};
	xcb_configure_window(mApplication->mConnection, mId, Mask, ValueList);
	xcb_flush(mApplication->mConnection);
}

void WindowT::setTitle(char const * String)
{
	xcb_change_property(
		mApplication->mConnection, XCB_PROP_MODE_REPLACE, mId, mApplication->mWmNameAtom,
		mApplication->mStringAtom, 8, strlen(String), String);

	xcb_flush(mApplication->mConnection);
}

}
}

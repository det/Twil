#include "Application.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Platform {

ApplicationT::ApplicationT() :
	mRunning{false}
{
	mDisplay = XOpenDisplay(0);
	if (mDisplay == nullptr) throw std::runtime_error{"Unable to open display"};

	mWmState = XInternAtom(mDisplay, "_NET_WM_STATE", False);
	mWmFullScreen = XInternAtom(mDisplay, "_NET_WM_STATE_FULLSCREEN", False);
	mWmDeleteWindow = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);

	static int VisualAttributes[] = {
		GLX_X_RENDERABLE ,  True,
		GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,    GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_ALPHA_SIZE,     8,
		GLX_DEPTH_SIZE,     16,
		GLX_DOUBLEBUFFER,   True,
		GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB, True,
		None
	};

	int FramebufferCount;
	auto Screen = DefaultScreen(mDisplay);
	mFramebufferConfigs = glXChooseFBConfig(mDisplay, Screen, VisualAttributes, &FramebufferCount);

	if (mFramebufferConfigs == nullptr) {
		throw std::runtime_error{"Unable to find matching video mode"};
	}

	mVisual = glXGetVisualFromFBConfig(mDisplay, mFramebufferConfigs[0]);
	auto Root = RootWindow(mDisplay, mVisual->screen);
	mColormap = XCreateColormap(mDisplay, Root, mVisual->visual, AllocNone);

	mWindowAttributes.colormap = mColormap;
	mWindowAttributes.background_pixmap = None;
	mWindowAttributes.border_pixel = 0;
	mWindowAttributes.event_mask =
		EnterWindowMask |
		LeaveWindowMask |
		PointerMotionMask |
		ButtonPressMask |
		ButtonReleaseMask |
		KeyPressMask |
		KeyReleaseMask |
		StructureNotifyMask |
		ExposureMask;

	using GlXCreateContextAttribsARBProcT = GLXContext (*) (
		Display *, GLXFBConfig, GLXContext, Bool, int const *
	);

	auto Symbol = reinterpret_cast<GLubyte const *>("glXCreateContextAttribsARB");
	auto Function = glXGetProcAddressARB(Symbol);
	auto glXCreateContextAttribsARB = reinterpret_cast<GlXCreateContextAttribsARBProcT>(Function);

	int ContextAttribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 3,
		None
	};
 
	auto & Config = mFramebufferConfigs[0];
	mContextId = glXCreateContextAttribsARB(mDisplay, Config, 0, True, ContextAttribs);
	if (mContextId == 0) throw std::runtime_error{"Unable to create OpenGL context"};

	Gl::ContextT::initialize();
}

ApplicationT::~ApplicationT()
{
	glXDestroyContext(mDisplay, mContextId);
	XFreeColormap(mDisplay, mColormap);
	XFree(mFramebufferConfigs);
	XFree(mVisual);
	XCloseDisplay(mDisplay);
}

void ApplicationT::stop()
{
	mRunning = false;
}


}
}

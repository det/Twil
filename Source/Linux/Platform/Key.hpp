#pragma once

#include <X11/keysym.h>
#include <X11/Xlib.h>

#undef Button1
#undef Button2
#undef Button3
#undef Button4
#undef Button5

namespace Twil {
namespace Platform {

enum class Key
{
	BackSpace = XK_BackSpace,
	Tab = XK_Tab,
	LineFeed = XK_Linefeed,
	Clear = XK_Clear,
	Return = XK_Return,
	Pause = XK_Pause,
	ScrollLock = XK_Scroll_Lock,
	SysReq = XK_Sys_Req,
	Escape = XK_Escape,
	Delete = XK_Delete,

	Home = XK_Home,
	Left = XK_Left,
	Up = XK_Up,
	Right = XK_Right,
	Down = XK_Down,
	Prior = XK_Prior,
	PageUp = XK_Page_Up,
	Next = XK_Next,
	PageDown = XK_Page_Down,
	End = XK_End,
	Begin = XK_Begin,

	KPSpace = XK_KP_Space,
	KPTab = XK_KP_Tab,
	KPEnter = XK_KP_Enter,
	KPF1 = XK_KP_F1,
	KPF2 = XK_KP_F2,
	KPF3 = XK_KP_F3,
	KPF4 = XK_KP_F4,
	KPHome = XK_KP_Home,
	KPLeft = XK_KP_Left,
	KPUp = XK_KP_Up,
	KPRight = XK_KP_Right,
	KPDown = XK_KP_Down,
	KPPrior = XK_KP_Prior,
	KPPage_Up = XK_KP_Page_Up,
	KPNext = XK_KP_Next,
	KPPage_Down = XK_KP_Page_Down,
	KPEnd = XK_KP_End,
	KPBegin = XK_KP_Begin,
	KPInsert = XK_KP_Insert,
	KPDelete = XK_KP_Delete,
	KPEqual = XK_KP_Equal,
	KPMultiply = XK_KP_Multiply,
	KPAdd = XK_KP_Add,
	KPSeparator = XK_KP_Separator,
	KPSubtract = XK_KP_Subtract,
	KPDecimal = XK_KP_Decimal,
	KPDivide = XK_KP_Divide,

	KP_0 = XK_KP_0,
	KP_1 = XK_KP_1,
	KP_2 = XK_KP_2,
	KP_3 = XK_KP_3,
	KP_4 = XK_KP_4,
	KP_5 = XK_KP_5,
	KP_6 = XK_KP_6,
	KP_7 = XK_KP_7,
	KP_8 = XK_KP_8,
	KP_9 = XK_KP_9,

	F1 = XK_F1,
	F2 = XK_F2,
	F3 = XK_F3,
	F4 = XK_F4,
	F5 = XK_F5,
	F6 = XK_F6,
	F7 = XK_F7,
	F8 = XK_F8,
	F9 = XK_F9,
	F10 = XK_F10,
	F11 = XK_F11,
	F12 = XK_F12,
	F13 = XK_F13,
	F14 = XK_F14,
	F15 = XK_F15,
	F16 = XK_F16,
	F17 = XK_F17,
	F18 = XK_F18,
	F19 = XK_F19,
	F20 = XK_F20,
	F21 = XK_F21,
	F22 = XK_F22,
	F23 = XK_F23,
	F24 = XK_F24,
	F25 = XK_F25,
	F26 = XK_F26,
	F27 = XK_F27,
	F28 = XK_F28,
	F29 = XK_F29,
	F30 = XK_F30,
	F31 = XK_F31,
	F32 = XK_F32,
	F33 = XK_F33,
	F34 = XK_F34,
	F35 = XK_F35,

	ShiftLeft = XK_Shift_L,
	ShiftRight = XK_Shift_R,
	ControlLeft = XK_Control_L,
	ControlRight = XK_Control_R,
	CapsLock = XK_Caps_Lock,
	ShiftLock = XK_Shift_Lock,

	MetaLeft = XK_Meta_L,
	MetaRight = XK_Meta_R,
	AltLeft = XK_Alt_L,
	AltRight = XK_Alt_R,
	SuperLeft = XK_Super_L,
	SuperRight = XK_Super_R,
	HyperLeft = XK_Hyper_L,
	HyperRight = XK_Hyper_R,

	Space = XK_space,
	Exclamation = XK_exclam,
	QuoteDouble = XK_quotedbl,
	NumberSign = XK_numbersign,
	Dollar = XK_dollar,
	Percent = XK_percent,
	Ampersand = XK_ampersand,
	Apostrophe = XK_apostrophe,
	QuoteRight = XK_quoteright,
	ParenLeft = XK_parenleft,
	ParenRight = XK_parenright,
	Asterisk = XK_asterisk,
	Plus = XK_plus,
	Comma = XK_comma,
	Minus = XK_minus,
	Period = XK_period,
	Slash = XK_slash,
	N0 = XK_0,
	N1 = XK_1,
	N2 = XK_2,
	N3 = XK_3,
	N4 = XK_4,
	N5 = XK_5,
	N6 = XK_6,
	N7 = XK_7,
	N8 = XK_8,
	N9 = XK_9,
	Colon = XK_colon,
	SemiColon = XK_semicolon,
	Less = XK_less,
	Equal = XK_equal,
	Greater = XK_greater,
	Question = XK_question,
	At = XK_at,
	BracketLeft = XK_bracketleft,
	BackSlash = XK_backslash,
	BracketRight = XK_bracketright,
	AsciiCircum = XK_asciicircum,
	Underscore = XK_underscore,
	Grave = XK_grave,
	QuoteLeft = XK_quoteleft,
	A = XK_a,
	B = XK_b,
	C = XK_c,
	D = XK_d,
	E = XK_e,
	F = XK_f,
	G = XK_g,
	H = XK_h,
	I = XK_i,
	J = XK_j,
	K = XK_k,
	L = XK_l,
	M = XK_m,
	N = XK_n,
	O = XK_o,
	P = XK_p,
	Q = XK_q,
	R = XK_r,
	S = XK_s,
	T = XK_t,
	U = XK_u,
	V = XK_v,
	W = XK_w,
	X = XK_x,
	Y = XK_y,
	Z = XK_z,
	BraceLeft = XK_braceleft,
	Bar = XK_bar,
	BraceRight = XK_braceright,
	AsciiTilde = XK_asciitilde
};

enum class Mod
{

	Button1 = Button1Mask,
	Button2 = Button2Mask,
	Button3 = Button3Mask,
	Button4 = Button4Mask,
	Button5 = Button5Mask,
	Shift = ShiftMask,
	Lock = LockMask,
	Control = ControlMask,
	Mod1 = Mod1Mask,
	Mod2 = Mod2Mask,
	Mod3 = Mod3Mask,
	Mod4 = Mod4Mask,
	Mod5 = Mod5Mask
};

}
}

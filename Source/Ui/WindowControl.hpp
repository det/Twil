#pragma once

namespace Twil {
namespace Ui {

class WindowControl {
	private:
	bool mNeedsRedraw;

	public:
	WindowControl();

	void setNeedsRedraw(bool);
	bool getNeedsRedraw();
};

}
}

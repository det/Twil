#pragma once

namespace Twil {
namespace Ui {

template<bool, bool>
class Resizable;

template<>
class Resizable<false, false>
{
	public:
	virtual ~Resizable() {}
};

template<>
class Resizable<true, false>
{
	public:
	virtual ~Resizable() {}
	virtual void setWidth(unsigned short) = 0;
};

template<>
class Resizable<false, true>
{
	public:
	virtual ~Resizable() {}
	virtual void setHeight(unsigned short) = 0;
};

template<>
class Resizable<true, true>
{
	public:
	virtual ~Resizable() {}
	virtual void setWidth(unsigned short) = 0;
	virtual void setHeight(unsigned short) = 0;
};

}
}

#pragma once

#include "Gl/Context.hpp"

#include <png.h>
#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	GLuint mId;

	public:
	void Load(char const *);

	void Bind() const;
};

}
}

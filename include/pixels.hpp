#ifndef PIXELS_HPP
#define PIXELS_HPP

#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <vector>

namespace xd {

class Pixels {
private:
	std::vector<GLubyte> data;
	bool resizeFlag;
	bool readFlag;

public:
	Pixels();

	class Proxy {
	private:
		Pixels& outer;
		int index, x, y;

	public:
		Proxy(Pixels& outer, int index);
		void operator=(glm::vec4 color);
		operator glm::vec4 const &();
	};

	Proxy operator[](int index);
	void lazyResize();
	void lazyRead();
};

} // namespace xd

#endif /* PIXELS_HPP */

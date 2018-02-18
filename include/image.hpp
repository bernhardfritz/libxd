#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <vector>

namespace xd {

class Image {
public:
	GLuint texture;
	int width, height;

	class ImagePixels {
	private:
		Image& image;
		std::vector<GLubyte> data;
		bool downloadFlag;
		bool uploadFlag;

	public:
		ImagePixels(Image& image);

		class ImageProxy {
		private:
			ImagePixels& outer;
			int index, x, y;

		public:
			ImageProxy(ImagePixels& outer, int index);
			void operator=(glm::vec4 color);
			operator glm::vec4 const &();
		};

		ImageProxy operator[](int index);

		void uploadIfNecessary();
	};

	ImagePixels pixels;

	Image();
	~Image();
};

} // namespace xd

#endif /* IMAGE_HPP */

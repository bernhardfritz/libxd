#include <xd/xd.hpp>
#include <xd/shaderprogram.hpp>
#include <xd/settings.hpp>
#include <xd/ellipse.hpp>
#include <xd/rect.hpp>
#include <xd/triangle.hpp>
#include <xd/vs.hpp>
#include <xd/gs.hpp>
#include <xd/fs.hpp>
#include <xd/font_vs.hpp>
#include <xd/font_fs.hpp>
#include <xd/image_vs.hpp>
#include <xd/image_fs.hpp>
#include <xd/passthrough.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stack>
#include <sstream>
#include <algorithm>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <stb/stb_image.h>

namespace xd {

int width = 100, height = 100, frameCount = 0;
Pixels pixels;
Passthrough* passthrough = nullptr;

static GLFWwindow* window;
static bool loop_ = true;

static int framebufferWidth, framebufferHeight;
static int displayDensity_;
static mt19937 rng;
static mat4 viewMatrix, projectionMatrix;

static Shape* ELLIPSE = NULL;
static Shape* RECT = NULL;
static Shape* TRIANGLE = NULL;

static stack<Settings> settingsStack;

static ShaderProgram* shaderProgram = nullptr;
static ShaderProgram* fontShaderProgram = nullptr;
static ShaderProgram* imageShaderProgram = nullptr;

static RenderPass* renderPass_ = nullptr;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void updateWindowSize(int width_, int height_) {
	width = width_;
	height = height_;
}

static void window_size_callback(GLFWwindow* window, int width_, int height_) {
	updateWindowSize(width_, height_);
}

static void initShapes() {
	ELLIPSE = new Ellipse(framebufferWidth, framebufferHeight);
	RECT = new Rect(framebufferWidth, framebufferHeight);
	TRIANGLE = new Triangle(framebufferWidth, framebufferHeight);
}

static void destroyShapes() {
	delete ELLIPSE;
	ELLIPSE = 0;
	delete RECT;
	RECT = 0;
	delete TRIANGLE;
	TRIANGLE = 0;
}

static void updateFramebufferSize(int framebufferWidth_, int framebufferHeight_) {
	framebufferWidth = framebufferWidth_;
	framebufferHeight = framebufferHeight_;
	
	destroyShapes();
	initShapes();

	projectionMatrix = ortho(0.0f, (float)framebufferWidth, (float)framebufferHeight, 0.0f);

	glViewport(0, 0, framebufferWidth, framebufferHeight);

	pixels.lazyResize();

	for (RenderPass*& instance : RenderPass::instances) {
		instance->initFramebufferTexture();
	}
	
	redraw();
}

static void framebuffer_size_callback(GLFWwindow* window, int framebufferWidth_, int framebufferHeight_) {
	updateFramebufferSize(framebufferWidth_, framebufferHeight_);
}

int displayDensity() {
	return displayDensity_;
}

Image* loadImage(const string& filename) {
	Image* img = new Image();
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename.c_str(), &img->width, &img->height, NULL, 4);
	if (!data) {
		fprintf(stderr, "%s\n", stbi_failure_reason());
		delete img;
		return nullptr;
	}
	glGenTextures(1, &img->texture);
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return img;
}

float millis() {
	return glfwGetTime() * 1000.0f;
}

void size(int width_, int height_) {
	width = width_;
	height = height_;
	glfwSetWindowSize(window, width, height);
}

float random(float min, float max) {
    uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

void randomSeed(unsigned int seed) {
	rng.seed(seed);
}

void loop() {
	loop_ = true;
}

void noLoop() {
	loop_ = false;
}

Settings& peek() {
	return settingsStack.top();
}

void pop_() {
	settingsStack.pop();
}

void pop() {
	if (settingsStack.size() > 1) {
		pop_();
	}
}

void push_() {
	settingsStack.push(Settings());
}

void push() {
	settingsStack.push(peek());
}

void redraw() {
	if (passthrough) {
		passthrough->begin();
	}

	shaderProgram->bind();

	Settings& settings = peek();
	settings.modelMatrix = mat4(1.0f);
	draw();
	frameCount++;
	// depending on the sketch there could be some forgotten items on the stack
	while(settingsStack.size() > 1) {
		pop();
	}

	if (passthrough) {
		passthrough->end();
	}

	settings.modelMatrix = mat4(1.0f);
	if (renderPass_) {
		renderPass_->render(true);
	}
	glfwSwapBuffers(window);
}

void background(vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
	pixels.lazyRead();
}

void clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	pixels.lazyRead();
}

void ellipseMode(DrawMode drawMode) {
	Settings& settings = peek();
	settings.ellipseMode = drawMode;
}

void fill(vec4 color) {
	Settings& settings = peek();
	settings.fillColor = color;
	settings.doFill = 1;
}

void imageMode(DrawMode drawMode) {
	Settings& settings = peek();
	settings.imageMode = drawMode;
}

void noFill() {
	Settings& settings = peek();
	settings.doFill = 0;
}

void noStroke() {
	Settings& settings = peek();
	settings.doStroke = 0;
}

void rectMode(DrawMode drawMode) {
	Settings& settings = peek();
	settings.rectMode = drawMode;
}

void stroke(vec4 color) {
	Settings& settings = peek();
	settings.strokeColor = color;
	settings.doStroke = 1;
}

void strokeWeight(float weight) {
	Settings& settings = peek();
	settings.strokeWeight = weight;
}

void textFont(Font& font) {
	Settings& settings = peek();
	settings.font = &font;
}

void textSize(float theSize) {
	Settings& settings = peek();
	settings.textSize = theSize;
}

void applyMatrix(float a, float b, float c, float d, float e, float f) {
	Settings& settings = peek();
	mat4 m = mat4(
		a, b, 0, 0,
		c, d, 0, 0,
		e, f, 1, 0,
		0, 0, 0, 1
	);
	settings.modelMatrix = m * settings.modelMatrix;
}

void resetMatrix() {
	Settings& settings = peek();
	settings.modelMatrix = mat4(1.0f);
}

void rotate(float rad) {
	Settings& settings = peek();
	settings.modelMatrix = rotate(settings.modelMatrix, rad, vec3(0.0f, 0.0f, 1.0f));
}

void scale(float x, float y) {
	Settings& settings = peek();
	settings.modelMatrix = scale(settings.modelMatrix, vec3(x, y, 1.0f));
}

void translate(float x, float y) {
	Settings& settings = peek();
	settings.modelMatrix = translate(settings.modelMatrix, vec3(x * displayDensity(), y * displayDensity(), 0.0f));
}

void updateUniforms() {
	ShaderProgram* boundShaderProgram = ShaderProgram::getBoundShaderProgram();
	if (boundShaderProgram == nullptr) {
		return;
	}

	Settings& settings = peek();

	mat4x4 MVP = projectionMatrix * viewMatrix * settings.modelMatrix;
	boundShaderProgram->setUniform("uMVP", MVP);

	if (boundShaderProgram == shaderProgram) {
		vec2 WIN_SCALE = vec2(framebufferWidth / 2, framebufferHeight / 2);
		boundShaderProgram->setUniform("uWIN_SCALE", WIN_SCALE);

		boundShaderProgram->setUniform("uFillColor", settings.fillColor);
		boundShaderProgram->setUniform("uStrokeColor", settings.strokeColor);
		boundShaderProgram->setUniform("uDoFill", settings.doFill);
		boundShaderProgram->setUniform("uDoStroke", settings.doStroke);
		boundShaderProgram->setUniform("uStrokeWeight", settings.strokeWeight);
	}
}

void ellipse(float a, float b, float c, float d) {
	push();
	Settings& settings = peek();
	switch(settings.ellipseMode) {
		case CENTER:
			translate(a, b);
			scale(c * displayDensity() / framebufferWidth, d * displayDensity() / framebufferHeight);
			break;
		case CORNER:
			translate(a + c / 2, b + d / 2);
			scale(c * displayDensity() / framebufferWidth, d * displayDensity() / framebufferHeight);
			break;
		case CORNERS:
			if (a > c) {
				swap(a, c);
			}
			if (b > d) {
				swap(b, d);
			}
			translate(a + (c - a) / 2, b + (d - b) / 2);
			scale((c - a) * displayDensity() / framebufferWidth , (d - b) * displayDensity() / framebufferHeight);
			break;
		case RADIUS:
			translate(a, b);
			scale(c * 2 * displayDensity() / framebufferWidth, d * 2 * displayDensity() / framebufferHeight);
			break;
	}
	updateUniforms();
	ELLIPSE->draw();
	pixels.lazyRead();
	pop();
}

void image(Image* img, float dx, float dy, float dWidth, float dHeight, float sx, float sy, float sWidth, float sHeight) {
	Settings& settings = peek();
	imageShaderProgram->bind();
	img->pixels.uploadIfNecessary();
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	imageShaderProgram->setUniform("uTexture", 0);
	imageShaderProgram->setUniform("uTintColor", settings.tintColor);
	imageShaderProgram->setUniform("uDoTint", settings.doTint);
	mat4 textureMatrix = mat4(1.0f);
	textureMatrix = translate(textureMatrix, vec3(sx / img->width, (img->height - sy - sHeight) / img->height, 0.0f));
	textureMatrix = scale(textureMatrix, vec3(sWidth / img->width, sHeight / img->height, 1.0f));
	imageShaderProgram->setUniform("uTextureMatrix", textureMatrix);
	rect(dx, dy, dWidth, dHeight, true);
	glBindTexture(GL_TEXTURE_2D, 0);
	shaderProgram->bind();
}

void image(Image* img, float x, float y, float w, float h) {
	image(img, x, y, w, h, 0.0f, 0.0f, img->width, img->height);
}

void tint(vec4 color) {
	Settings& settings = peek();
	settings.tintColor = color;
	settings.doTint = 1;
}

void noTint() {
	Settings& settings = peek();
	settings.doTint = 0;
}

void text(const string& str, float x, float y) {
	Settings& settings = peek();
	fontShaderProgram->bind();
	settings.font->texture->bind();
	fontShaderProgram->setUniform("uTexture", 0);
	fontShaderProgram->setUniform("uFillColor", settings.fillColor);
	fontShaderProgram->setUniform("uStrokeColor", settings.strokeColor);
	fontShaderProgram->setUniform("uDoFill", settings.doFill);
	fontShaderProgram->setUniform("uDoStroke", settings.doStroke);
	fontShaderProgram->setUniform("uStrokeWeight", settings.strokeWeight);

	push();
	translate(x, y);
	float s = (2.0f * settings.textSize) / (settings.font->f.height * displayDensity());
	scale(s, s);

	x = 0.0f;
	y = 0.0f;

	for (const char& ch : str) {
		xd_texture_glyph_t *glyph = 0;
      	for (int j = 0; j < settings.font->f.glyphs_count; j++) {
			if (settings.font->f.glyphs[j].codepoint == ch) {
				glyph = &settings.font->f.glyphs[j];
				break;
         	}
		}
		if (!glyph) {
			continue;
		}

		Shape shape;

		Vertex vertices_arr[] = {
			{ vec2(0.0f, 0.0f), vec2(glyph->s0, glyph->t0), 1.0f },
			{ vec2(0.0f, framebufferHeight), vec2(glyph->s0, glyph->t1), 0.0f },
			{ vec2(framebufferWidth, 0.0f), vec2(glyph->s1, glyph->t0), 0.0f },
			{ vec2(framebufferWidth, framebufferHeight), vec2(glyph->s1, glyph->t1), 1.0f }
		};
		vector<Vertex> vertices(vertices_arr, vertices_arr + sizeof(vertices_arr) / sizeof(vertices_arr[0]));

		unsigned short indices_arr[] = {
			0, 1, 2,
			2, 1, 3
		};
		vector<unsigned short> indices(indices_arr, indices_arr + sizeof(indices_arr) / sizeof(indices_arr[0]));

		shape.init(vertices, indices);

		push();
		translate(x + glyph->offset_x, y - glyph->offset_y);
		scale((float) glyph->width / width, (float) glyph->height / height);

		Settings& settings = peek();
		mat4x4 MVP = projectionMatrix * viewMatrix * settings.modelMatrix;
		fontShaderProgram->setUniform("uMVP", MVP);

		shape.draw();
		pop();

		x += glyph->advance_x;
	}

	pop();

	settings.font->texture->unbind();

	shaderProgram->bind();

	pixels.lazyRead();
}

void line(float x1, float y1, float x2, float y2) {
	vec2 a = vec2(x1, y1);
	vec2 b = vec2(x2, y2);
	vec2 r = b - a;
	float angle = atan2f(r.y, r.x);

	push();
	Settings& settings = peek();
	settings.fillColor = settings.strokeColor;
	settings.doFill = settings.doStroke;
	settings.doStroke = 0;
	translate(x1 + sinf(angle) * settings.strokeWeight / 2.0f, y1 - cosf(angle) * settings.strokeWeight / 2.0f);
	rotate(angle);
	rect(0.0f, 0.0f, length(r), settings.strokeWeight);
	pop();
}

void point(float x, float y) {
	push();
	Settings& settings = peek();
	settings.fillColor = settings.strokeColor;
	settings.doFill = settings.doStroke;
	settings.doStroke = 0;
	if (settings.strokeWeight < 1.1f) {
		rect(x, y, 1.0f, 1.0f);
	} else {
		ellipse(x + 0.5f, y + 0.5f, settings.strokeWeight, settings.strokeWeight);
	}
	pop();
}

void rect(float a, float b, float c, float d, bool useImageMode) {
	push();
	Settings& settings = peek();
	switch(useImageMode ? settings.imageMode : settings.rectMode) {
		case CENTER:
			translate(a - c / 2, b - d / 2);
			scale(c * displayDensity() / framebufferWidth , d * displayDensity() / framebufferHeight);
			break;
		case CORNER:
			translate(a, b);
			scale(c * displayDensity() / framebufferWidth , d * displayDensity() / framebufferHeight);
			break;
		case CORNERS:
			if (a > c) {
				swap(a, c);
			}
			if (b > d) {
				swap(b, d);
			}
			translate(a, b);
			scale((c - a) * displayDensity() / framebufferWidth , (d - b) * displayDensity() / framebufferHeight);
			break;
		case RADIUS:
			translate(a - c, b - d);
			scale(c * 2 * displayDensity() / framebufferWidth , d * 2 * displayDensity() / framebufferHeight);
			break;
	}
	updateUniforms();
	RECT->draw();
	pixels.lazyRead();
	pop();
}

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	if (!ccw(x1, y1, x2, y2, x3, y3)) {
		swap(x1, x3);
		swap(y1, y3);
	}
	mat4 A = mat4(
		            0.0f,              0.0f, 1.0f, 0.0f,
		            0.0f, framebufferHeight, 1.0f, 0.0f,
		framebufferWidth,              0.0f, 1.0f, 0.0f,
		            0.0f,              0.0f, 0.0f, 1.0f
	);
	mat4 B = mat4(
		x1 * displayDensity(), y1 * displayDensity(), 1.0f, 0.0f,
		x2 * displayDensity(), y2 * displayDensity(), 1.0f, 0.0f,
		x3 * displayDensity(), y3 * displayDensity(), 1.0f, 0.0f,
		                 0.0f,                  0.0f, 0.0f, 1.0f
	);
	mat4 invA = inverse(A);
	mat4 M = B * invA;

	push();
	Settings& settings = peek();
	translate(x1, y1);
	settings.modelMatrix = settings.modelMatrix * M;
	updateUniforms();
	TRIANGLE->draw();
	pixels.lazyRead();
	pop();
}

void renderPass(RenderPass* thePass) {
	renderPass_ = thePass;
}

} // namespace xd

using namespace xd;

int main(int argc, char* argv[]) {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "xD", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);

	shaderProgram = new ShaderProgram();
	shaderProgram->createVertexShader(vs);
	shaderProgram->createGeometryShader(gs);
	shaderProgram->createFragmentShader(fs);
	shaderProgram->link();

	shaderProgram->createUniform("uMVP");
	shaderProgram->createUniform("uWIN_SCALE");
	shaderProgram->createUniform("uFillColor");
	shaderProgram->createUniform("uStrokeColor");
	shaderProgram->createUniform("uDoFill");
	shaderProgram->createUniform("uDoStroke");
	shaderProgram->createUniform("uStrokeWeight");

	fontShaderProgram = new ShaderProgram();
	fontShaderProgram->createVertexShader(font_vs);
	fontShaderProgram->createFragmentShader(font_fs);
	fontShaderProgram->link();
	
	fontShaderProgram->createUniform("uMVP");
	fontShaderProgram->createUniform("uTexture");
	fontShaderProgram->createUniform("uFillColor");
	fontShaderProgram->createUniform("uStrokeColor");
	fontShaderProgram->createUniform("uDoFill");
	fontShaderProgram->createUniform("uDoStroke");
	fontShaderProgram->createUniform("uStrokeWeight");

	imageShaderProgram = new ShaderProgram();
	imageShaderProgram->createVertexShader(image_vs);
	imageShaderProgram->createFragmentShader(image_fs);
	imageShaderProgram->link();

	imageShaderProgram->createUniform("uMVP");
	imageShaderProgram->createUniform("uTexture");
	imageShaderProgram->createUniform("uTextureMatrix");
	imageShaderProgram->createUniform("uTintColor");
	imageShaderProgram->createUniform("uDoTint");

	vec3 eye = vec3(0.0f, 0.0f, 0.0f);
	vec3 center = vec3(0.0f, 0.0f, -1.0f);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	viewMatrix = lookAt(eye, center, up);

	randomSeed(random_device()());

	push_();
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	displayDensity_ = framebufferWidth / width;
	opensans.init();
	passthrough = new Passthrough();
	renderPass(passthrough);
	setup();
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	updateFramebufferSize(framebufferWidth, framebufferHeight);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	double previousTime = glfwGetTime();
	int fps = 0;
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - previousTime >= 1.0) {
			ostringstream s;
			s << "xD @ " << fps << " fps";
			glfwSetWindowTitle(window, s.str().c_str());
			fps = 0;
			previousTime = currentTime;
		}

		if (loop_) {
	    	redraw();
		}

        glfwPollEvents();

		int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (state == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
	destroy();
	pop_();

	destroyShapes();
	delete shaderProgram;
	delete fontShaderProgram;
	delete imageShaderProgram;
	delete passthrough;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

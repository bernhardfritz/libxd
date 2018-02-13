#include "xd.hpp"
#include "shader.hpp"
#include "settings.hpp"
#include "ellipse.hpp"
#include "rect.hpp"
#include "triangle.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stack>
#include <sstream>
#include <algorithm>
#include <random>

int width = 100, height = 100;
Pixels pixels;

static GLFWwindow* window;
static bool loop_ = true;

static GLuint program;
static int framebufferWidth, framebufferHeight;
static int displayDensity_;
static mt19937 rng;
static mat4 viewMatrix, projectionMatrix;

static GLint uMVP;
static GLint uWIN_SCALE;
static GLint uFillColor;
static GLint uStrokeColor;
static GLint uDoFill;
static GLint uDoStroke;
static GLfloat uStrokeWeight;
static GLint uTexture;
static GLint uDoTexture;

static Shape* ELLIPSE = NULL;
static Shape* RECT = NULL;
static Shape* TRIANGLE = NULL;

static stack<Settings*> settingsStack;

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

	background(vec4(vec3(0.3f), 1.0f));
	pixels.lazyResize();
	
	redraw();
}

static void framebuffer_size_callback(GLFWwindow* window, int framebufferWidth_, int framebufferHeight_) {
	updateFramebufferSize(framebufferWidth_, framebufferHeight_);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int displayDensity() {
	return displayDensity_;
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

Settings* peek() {
	Settings* settings = settingsStack.top();
	return settings;
}

void pop_() {
	Settings* settings = settingsStack.top();
	settingsStack.pop();
	settings_destroy(settings);
	settings = NULL;
}

void pop() {
	if (settingsStack.size() > 1) {
		pop_();
	}
}

void push_() {
	Settings* settings;
	settings_new(&settings);
	settingsStack.push(settings);
}

void push() {
	Settings* peekSettings = peek();
	Settings* pushSettings = (Settings*) malloc(sizeof(Settings));
	memcpy(pushSettings, peekSettings, sizeof(Settings));
	settingsStack.push(pushSettings);
}

void redraw() {
	glUseProgram(program);

	Settings* peekSettings = peek();
	peekSettings->modelMatrix = mat4(1.0f);
	draw();
	// depending on the sketch there could be some forgotten items on the stack
	while(settingsStack.size() > 1) {
		pop();
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
	Settings* settings = peek();
	settings->ellipseMode = drawMode;
}

void fill(vec4 color) {
	Settings* settings = peek();
	settings->fillColor = color;
	settings->doFill = 1;
}

void noFill() {
	Settings* settings = peek();
	settings->doFill = 0;
}

void noStroke() {
	Settings* settings = peek();
	settings->doStroke = 0;
}

void rectMode(DrawMode drawMode) {
	Settings* settings = peek();
	settings->rectMode = drawMode;
}

void stroke(vec4 color) {
	Settings* settings = peek();
	settings->strokeColor = color;
	settings->doStroke = 1;
}

void strokeWeight(float weight) {
	Settings* settings = peek();
	settings->strokeWeight = weight;
}

void applyMatrix(float a, float b, float c, float d, float e, float f) {
	Settings* settings = peek();
	mat4 m = mat4(
		a, b, 0, 0,
		c, d, 0, 0,
		e, f, 1, 0,
		0, 0, 0, 1
	);
	settings->modelMatrix = m * settings->modelMatrix;
}

void resetMatrix() {
	Settings* settings = peek();
	settings->modelMatrix = mat4(1.0f);
}

void rotate(float rad) {
	Settings* settings = peek();
	settings->modelMatrix = rotate(settings->modelMatrix, rad, vec3(0.0f, 0.0f, 1.0f));
}

void scale(float x, float y) {
	Settings* settings = peek();
	settings->modelMatrix = scale(settings->modelMatrix, vec3(x, y, 1.0f));
}

void translate(float x, float y) {
	Settings* settings = peek();
	settings->modelMatrix = translate(settings->modelMatrix, vec3(x * displayDensity(), y * displayDensity(), 0.0f));
}

void updateUniforms() {
	Settings* settings = peek();

	mat4x4 MVP = projectionMatrix * viewMatrix * settings->modelMatrix;
	glUniformMatrix4fv(uMVP, 1, GL_FALSE, (const GLfloat*) &MVP[0]);

	vec2 WIN_SCALE = vec2(framebufferWidth / 2, framebufferHeight / 2);
	glUniform2fv(uWIN_SCALE, 1, (const GLfloat*) &WIN_SCALE[0]);

	glUniform4fv(uFillColor, 1, (const GLfloat*) &settings->fillColor[0]);
	glUniform4fv(uStrokeColor, 1, (const GLfloat*) &settings->strokeColor[0]);
	glUniform1iv(uDoFill, 1, (const GLint*) &settings->doFill);
	glUniform1iv(uDoStroke, 1, (const GLint*) &settings->doStroke);
	glUniform1fv(uStrokeWeight, 1, (const GLfloat*) &settings->strokeWeight);
}

void ellipse(float a, float b, float c, float d) {
	push();
	Settings* settings = peek();
	switch(settings->ellipseMode) {
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

void image(Image* img, float x, float y) {
	img->pixels.uploadIfNecessary();
	glBindTexture(GL_TEXTURE_2D, img->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glUniform1i(uTexture, 0);
	glUniform1i(uDoTexture, 1);
	rect(x, y, 200.0f, 200.0f);
	glUniform1i(uDoTexture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void line(float x1, float y1, float x2, float y2) {
	vec2 a = vec2(x1, y1);
	vec2 b = vec2(x2, y2);
	vec2 r = b - a;
	float angle = atan2f(r.y, r.x);

	push();
	Settings* settings = peek();
	settings->fillColor = settings->strokeColor;
	settings->doFill = settings->doStroke;
	settings->doStroke = 0;
	translate(x1 + sinf(angle) * settings->strokeWeight / 2.0f, y1 - cosf(angle) * settings->strokeWeight / 2.0f);
	rotate(angle);
	rect(0.0f, 0.0f, length(r), settings->strokeWeight);
	pop();
}

void point(float x, float y) {
	push();
	Settings* settings = peek();
	settings->fillColor = settings->strokeColor;
	settings->doFill = settings->doStroke;
	settings->doStroke = 0;
	rect(x, y, 1.0f, 1.0f);
	pop();
}

void rect(float a, float b, float c, float d) {
	push();
	Settings* settings = peek();
	switch(settings->rectMode) {
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
	Settings* settings = peek();
	translate(x1, y1);
	settings->modelMatrix = settings->modelMatrix * M;
	updateUniforms();
	TRIANGLE->draw();
	pixels.lazyRead();
	pop();
}

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

	const char* c_str;

	string vs = readFile("vs.glsl");
	GLuint vertex_shader = createVertexShader(&(c_str=vs.c_str()));

	string gs = readFile("gs.glsl");
	GLuint geometry_shader = createGeometryShader(&(c_str=gs.c_str()));

	string fs = readFile("fs.glsl");
	GLuint fragment_shader = createFragmentShader(&(c_str=fs.c_str()));

	program = createProgram(3, vertex_shader, geometry_shader, fragment_shader);

	uMVP = createUniform(program, "uMVP");
	uWIN_SCALE = createUniform(program, "uWIN_SCALE");
	uFillColor = createUniform(program, "uFillColor");
	uStrokeColor = createUniform(program, "uStrokeColor");
	uDoFill = createUniform(program, "uDoFill");
	uDoStroke = createUniform(program, "uDoStroke");
	uStrokeWeight = createUniform(program, "uStrokeWeight");
	uTexture = createUniform(program, "uTexture");
	uDoTexture = createUniform(program, "uDoTexture");

	vec3 eye = vec3(0.0f, 0.0f, 0.0f);
	vec3 center = vec3(0.0f, 0.0f, -1.0f);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	viewMatrix = lookAt(eye, center, up);

	randomSeed(random_device()());

	push_();
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	displayDensity_ = framebufferWidth / width;
	setup();
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	updateFramebufferSize(framebufferWidth, framebufferHeight);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	double previousTime = glfwGetTime();
	int frameCount = 0;
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0) {
			ostringstream s;
			s << "xD @ " << frameCount << " fps";
			glfwSetWindowTitle(window, s.str().c_str());
			frameCount = 0;
			previousTime = currentTime;
		}

		if (loop_) {
	    	redraw();
		}

        glfwPollEvents();
	}
	destroy();
	pop_();

	destroyShapes();
	destroyProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

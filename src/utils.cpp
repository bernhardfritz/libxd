#include <xd/utils.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

namespace xd {

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

string readFile(const string& filename) {
	ifstream ifs(filename.c_str());
	stringstream ss;
	ss << ifs.rdbuf();
	return ss.str();
}

} // namespace xd

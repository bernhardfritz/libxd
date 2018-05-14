#ifndef UTILS_HPP
#define UTILS_HPP

#include <glm/fwd.hpp>
#include <string>

namespace xd {

float map(float x, float in_min, float in_max, float out_min, float out_max);
std::string readFile(const std::string& filename);

} // namespace xd

#endif /* UTILS_HPP */

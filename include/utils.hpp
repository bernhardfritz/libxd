#ifndef UTILS_HPP
#define UTILS_HPP

#include "image.hpp"
#include <glm/fwd.hpp>
#include <string>

void swap(int* a, int* b);
float map(float x, float in_min, float in_max, float out_min, float out_max);
std::string readFile(std::string filename);
Image* loadImage(const char* filename);

#endif /* UTILS_HPP */

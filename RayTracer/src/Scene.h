#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Sphere {
	glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
	float Radius = 1.0f;
	glm::vec3 Colour{1.0f, 0.0f, 0.0f};
	float Transparency = 1.0f;
};
struct Scene {
	std::vector<Sphere> Spheres;
};
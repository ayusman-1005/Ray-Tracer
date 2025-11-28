#pragma once	
#include <memory>
#include <Walnut/Image.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Ray.h"

class Renderer {
public:
	Renderer() = default;
	void OnResize(uint32_t width, uint32_t height);
	void Render(const Camera& camera);
 inline	std::shared_ptr<Walnut::Image> GetFinalImage() { return m_FinalImage; }

private:
	glm::vec4 trace_ray(const Ray& ray);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	float aspect_ratio;
	uint32_t* m_ImageData = 0;
};
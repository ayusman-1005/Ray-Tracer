#pragma once	
#include <memory>
#include <Walnut/Image.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

class Renderer {
public:
	Renderer() = default;
	void OnResize(uint32_t width, uint32_t height);
	void Render(const Scene& scene, const Camera& camera);
 inline	std::shared_ptr<Walnut::Image> GetFinalImage() { return m_FinalImage; }

private:
	glm::vec4 trace_ray(const Scene& scene, const Ray& ray);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	float aspect_ratio = 1.0f;
	uint32_t* m_ImageData = 0;
};
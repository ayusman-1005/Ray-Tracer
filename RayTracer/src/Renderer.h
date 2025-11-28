#pragma once	
#include <memory>
#include <Walnut/Image.h>
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer() = default;
	void OnResize(uint32_t width, uint32_t height);
	void Render();
 inline	std::shared_ptr<Walnut::Image> GetFinalImage() { return m_FinalImage; }

private:
	uint32_t SetPixel(glm::vec2 coord);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = 0;
public:
	glm::vec3 ray_origin = { 0.0f, 0.0f, 3.0f };
};
#pragma once	
#include <memory>
#include <Walnut/image.h>

class Renderer {
public:
	Renderer() = default;
	void OnResize(uint32_t width, uint32_t height);
	void Render();
 inline	std::shared_ptr<Walnut::Image> GetFinalImage() { return m_FinalImage; }
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = 0;
};
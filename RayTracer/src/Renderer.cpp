#include "Renderer.h"

void Renderer::OnResize(uint32_t width, uint32_t height) {
	if (m_FinalImage) {
		m_FinalImage->Resize(width,height); // also checks if resize is necessary inside
	}
	else {
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	delete[] m_ImageData;
	
	m_ImageData = new uint32_t[width * height];
}

//sample circle render
void Renderer::Render() {
	for (uint32_t j = 0; j < m_FinalImage->GetHeight(); ++j) {
		for (uint32_t i = 0; i < m_FinalImage->GetWidth(); ++i) {

			auto index = j * m_FinalImage->GetWidth() + i;

			glm::vec2 coord = { i / (float)m_FinalImage->GetWidth(), j / (float)m_FinalImage->GetHeight() };
			coord = coord * 2.0f - 1.0f;
			m_ImageData[index] = SetPixel(coord);
		}
	}


	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::SetPixel(glm::vec2 coord)
{   
	uint32_t col;
	glm::vec3 ray_direction(coord.x, coord.y, -1.0f);
	ray_direction = glm::normalize(ray_direction);
	float radius = 1.0f;
	float l = glm::dot(ray_direction, ray_direction);
	float m = 2.0f * glm::dot(ray_origin, ray_direction);
	float n = glm::dot(ray_origin, ray_origin) - radius * radius;
	float discr = m*m - 4.0f*l*n;

	if (discr < 0) {
		return 0xffffffff;
	}

	float t1 = (- m - glm::sqrt(discr)) / (2 * l);
	float t2 = (-m + glm::sqrt(discr)) / (2 * l);
	float t = (t1 > 0.0f) ? t1 : t2;
	if (t < 0) {
		return 0xffffffff;
	}

	uint8_t grey = (uint8_t)(glm::clamp(1.0f/t, 0.0f, 1.0f) * 255.0f);
	col = 0xffff0000 | (grey << 16) | (grey << 8) | grey; //AABBGGRR

	return col;

}


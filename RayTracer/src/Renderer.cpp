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


void Renderer::Render() {
	float	 CircleRad = 200.f;
	float	 Circle_O_X = m_FinalImage->GetWidth() / 2;
	float	 Circle_O_Y = m_FinalImage->GetHeight() / 2;
	for (uint32_t j = 0; j < m_FinalImage->GetHeight(); ++j) {
		for (uint32_t i = 0; i < m_FinalImage->GetWidth(); ++i) {

			auto index = j * m_FinalImage->GetWidth() + i;

			auto dx = i - Circle_O_X;
			auto dy = j - Circle_O_Y;
			auto DistanceSquared = dx * dx + dy * dy;
			auto RadiusSquared = CircleRad * CircleRad;

			if (DistanceSquared < RadiusSquared) {
				m_ImageData[index] = 0xffe5000;//AABBGGRR
			}
			else m_ImageData[index] = 0xffffe500; //AABBGGRR
		}
	}


	m_FinalImage->SetData(m_ImageData);
}
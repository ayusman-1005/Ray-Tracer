#include "Renderer.h"
#include "Ray.h"

namespace utils {
	uint32_t to_rgba(glm::vec4 colour) {
		uint8_t r = (uint8_t)(colour.r * 255.0f);
		uint8_t g = (uint8_t)(colour.g * 255.0f);
		uint8_t b = (uint8_t)(colour.b * 255.0f);
		uint8_t a = (uint8_t)(colour.a * 255.0f);

		return 0x00000000 | (a << 24) | (b << 16) | (g << 8) | r;
	}
}

void Renderer::OnResize(uint32_t width, uint32_t height) {
	if (m_FinalImage) {
		m_FinalImage->Resize(width,height); // also checks if resize is necessary inside
	}
	else {
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	delete[] m_ImageData;
	
	m_ImageData = new uint32_t[width * height];
	aspect_ratio = width/(float)height;
}

//sample sphere render
void Renderer::Render(const Scene& scene, const Camera& camera) {
	Ray ray;
	ray.Origin = camera.GetPosition();

	for (uint32_t j = 0; j < m_FinalImage->GetHeight(); ++j) {
		for (uint32_t i = 0; i < m_FinalImage->GetWidth(); ++i) {

			auto index = j * m_FinalImage->GetWidth() + i;
	        ray.Direction = camera.GetRayDirections()[index];
			auto colour = glm::clamp(trace_ray(scene, ray), glm::vec4(0.0f),glm::vec4(1.0f));

			m_ImageData[index] = utils::to_rgba(colour) ;
		}
	}


	m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::trace_ray(const Scene& scene, const Ray& ray)
{   
	glm ::vec4 defalut_colour{0.0f,0.0f, 0.0f, 1.0f};

	if (scene.Spheres.size() == 0) {
		return defalut_colour;
	}

	glm::vec3 light_dir(2.0f,0.0f, 0.0f);  // light
	light_dir = glm::normalize(light_dir);

	const Sphere* closest_sphere = nullptr;
	float hit_distance = FLT_MAX;

	for (const Sphere& sphere : scene.Spheres)
	{
		glm::vec3 origin = ray.Origin - sphere.Position;
		float l = glm::dot(ray.Direction, ray.Direction);
		float m = 2.0f * glm::dot(origin, ray.Direction);
		float n = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;
		float discr = m * m - 4.0f * l * n;
		//hit or not
		if (discr < 0) {
			continue;
		}
		//distance(if hit)
		float t1 = (-m - glm::sqrt(discr)) / (2 * l);
		float t2 = (-m + glm::sqrt(discr)) / (2 * l);
		float closest_distance = (t1 > 0.0f) ? t1 : t2;
		if (closest_distance < 0) {
			return defalut_colour; // should not happen
		}

		if (closest_distance < hit_distance) {
			hit_distance = closest_distance;
			closest_sphere = &sphere;
		}
	}

	if (closest_sphere == nullptr)
		return defalut_colour;



	glm::vec3 origin = ray.Origin - closest_sphere->Position; // camera shifing when sphere pos change



	//lighting
	glm::vec3 hit_position = origin + ray.Direction * hit_distance;
	glm::vec3 normal = glm::normalize(hit_position);
	float shaded = glm::max(glm::dot(normal, -light_dir),0.0f);


	// auto grey = glm::clamp((1.0f/(hit_distance*0.5f)), 0.0f, 1.0f); 
	
	return glm::vec4(closest_sphere->Colour * shaded ,1.0f); // rgba

}


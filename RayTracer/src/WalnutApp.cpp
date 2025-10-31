#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "Walnut/Timer.h"
#include <cmath>

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
private:
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = 0;
	uint32_t m_ViewPortWidth  = 0;
	uint32_t m_ViewPortHeight = 0;
	float	 m_LastRenderTime = 0.f;
	float	 CircleRad = 200.f;
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last Render Time: %0.3f ms", m_LastRenderTime);
		if (ImGui::Button("Render")) {
			Render();
		};
		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f)); // for filling the padding
		ImGui::Begin("Viewport");
		m_ViewPortWidth = ImGui::GetContentRegionAvail().x;
		m_ViewPortHeight = ImGui::GetContentRegionAvail().y;
		if (m_Image) {
			ImGui::Image(m_Image->GetDescriptorSet(), {
				(float)m_Image->GetWidth(),(float)m_Image->GetHeight() });
		}
		ImGui::End();
		ImGui::PopStyleVar();
		//Render(); // in loop for video
	}
	void Render(){
		Timer timer;
		if (m_ViewPortHeight == 0 || m_ViewPortWidth == 0) return;
		float	 Circle_O_X = m_ViewPortWidth / 2;
		float	 Circle_O_Y = m_ViewPortHeight / 2;
		if (!m_Image || m_ViewPortWidth != m_Image->GetWidth() || m_ViewPortHeight != m_Image->GetHeight()) {
			m_Image = std::make_shared<Image>(m_ViewPortWidth, m_ViewPortHeight, ImageFormat::RGBA);
			delete[] m_ImageData;

			m_ImageData = new uint32_t[m_ViewPortHeight * m_ViewPortWidth];
			for (uint32_t j = 0; j < m_ViewPortHeight; ++j) {
				for (uint32_t i = 0; i < m_ViewPortWidth; ++i) {
					auto index = j * m_ViewPortWidth + i;
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


			m_Image->SetData(m_ImageData);
		}
		m_LastRenderTime = timer.ElapsedMillis();
	}

};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Ray Tracer";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}
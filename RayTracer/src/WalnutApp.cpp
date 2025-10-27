#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
private:
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = 0;
	uint32_t m_ViewPortWidth  = 0;
	uint32_t m_ViewPortHeight = 0;
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		if (ImGui::Button("Render")) {
			Render();
		};
		ImGui::End();
		ImGui::Begin("Viewport");
		m_ViewPortWidth = ImGui::GetContentRegionAvail().x;
		m_ViewPortHeight = ImGui::GetContentRegionAvail().y;
		if (m_Image) {
			ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_Image->GetWidth(),(float)m_Image->GetHeight() });
		}
		ImGui::End();
	}
	void Render(){
		if (m_ViewPortHeight == 0 || m_ViewPortWidth == 0) return;
		if (!m_Image || m_ViewPortWidth != m_Image->GetWidth() || m_ViewPortHeight != m_Image->GetHeight()) {
			m_Image = std::make_shared<Image>(m_ViewPortWidth, m_ViewPortHeight, ImageFormat::RGBA);
			
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewPortHeight * m_ViewPortWidth];
			for (uint32_t i = 0; i < m_ViewPortHeight * m_ViewPortHeight; ++i) {
				m_ImageData[i] = 0xff0000ff;
			}
			m_Image->SetData(m_ImageData);
		}
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
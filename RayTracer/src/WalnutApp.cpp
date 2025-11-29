#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"
#include "Walnut/Timer.h"
#include <cmath>
#include "Renderer.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
private:
	Renderer m_Renderer;
	Camera   m_camera;
	Scene	 m_scene;
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = 0;
	uint32_t m_ViewPortWidth  = 0;
	uint32_t m_ViewPortHeight = 0;
	float	 m_LastRenderTime = 0.f;
	float    m_viewport_iterator = 0.0f;
public:
	ExampleLayer() :m_camera(45.0f,0.1f,100.0f)		// constructor for camera
	{	
		
		float radius = 1.0f;
		
		{
			Sphere sphere;
			sphere.Position = { 0.0f, 0.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.Colour = { 1.0f,0.0f,0.0f};
			m_scene.Spheres.push_back(sphere);
		}
		
		{
			Sphere sphere;
			sphere.Position = { 0.0f, 2.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.Colour = { 1.0f,1.0f,0.0f};
			m_scene.Spheres.push_back(sphere);
		}
	}

	virtual void OnUpdate(float ts) override {
		m_camera.OnUpdate(ts); // Otherwise drive the camera
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last Render Time: %0.3f ms", m_LastRenderTime);
		
		
		if (ImGui::Button("Render")) {
			Render();
		};
		ImGui::End();

		ImGui::Begin("Scene");
		for (int i =0; i < m_scene.Spheres.size(); i++) {
			ImGui::PushID(i); //imguim issue 
			ImGui::DragFloat3("Position", glm::value_ptr(m_scene.Spheres[i].Position), 0.1f);
			ImGui::DragFloat("Radius", &m_scene.Spheres[i].Radius, 0.1f);
			ImGui::ColorEdit3("colour", glm::value_ptr(m_scene.Spheres[i].Colour), 0.1f);
			ImGui::Separator();
			ImGui::PopID();
		}
		ImGui::End();


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f)); // for filling the padding
		ImGui::Begin("Viewport");
		m_ViewPortWidth = ImGui::GetContentRegionAvail().x;
		m_ViewPortHeight = ImGui::GetContentRegionAvail().y;
		// final image from class instance
		auto image = m_Renderer.GetFinalImage();
		if (image) {
			ImGui::Image(image->GetDescriptorSet(), {
				(float)image->GetWidth(),(float)image->GetHeight() },
				ImVec2(0,1),ImVec2(1,0));
		}
		ImGui::End();
		ImGui::PopStyleVar();
		Render(); // in loop for video
	}
	void Render(){
		Timer timer;

		m_Renderer.OnResize(m_ViewPortWidth, m_ViewPortHeight);
		m_camera.OnResize(m_ViewPortWidth, m_ViewPortHeight);
		m_Renderer.Render(m_scene,m_camera);

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
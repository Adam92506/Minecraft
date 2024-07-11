#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Renderer/Camera.h"

#include "Timestep.h"


namespace Minecraft
{

	class CameraController
	{
	public:
		CameraController() {}
		CameraController(const glm::vec3& position, const glm::vec3& rotation, float viewportWidth, float viewportHeight);

		void OnEvent(Event& e);

		void OnUpdate(Timestep ts);
		
		void SetPosition(const glm::vec3& position) { m_Position = position; m_Camera.SetPosition(m_Position); }
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; m_Camera.SetRotation(m_Rotation); }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		Camera m_Camera;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 180.0f, 0.0f };

		float m_TranslationSpeed = 1.0f, m_RotationSpeed = 90.0f;
	};

}
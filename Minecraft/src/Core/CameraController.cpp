#include "pch.h"
#include "CameraController.h"

#include "Input.h"

namespace Minecraft
{

	CameraController::CameraController(const glm::vec3& position, const glm::vec3& rotation, float viewportWidth, float viewportHeight)
		: m_Camera(position, rotation, viewportWidth, viewportHeight)
	{

	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(CameraController::OnWindowResizeEvent));
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= cos(glm::radians(m_Rotation.y)) * m_TranslationSpeed * ts;
			m_Position.z += sin(glm::radians(m_Rotation.y)) * m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += cos(glm::radians(m_Rotation.y)) * m_TranslationSpeed * ts;
			m_Position.z -= sin(glm::radians(m_Rotation.y)) * m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_Position.x -= cos(glm::radians(m_Rotation.y - 90.0f)) * m_TranslationSpeed * ts;
			m_Position.z += sin(glm::radians(m_Rotation.y - 90.0f)) * m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::S))
		{
			m_Position.x += cos(glm::radians(m_Rotation.y - 90.0f)) * m_TranslationSpeed * ts;
			m_Position.z -= sin(glm::radians(m_Rotation.y - 90.0f)) * m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::X))
		{
			m_Position.y += m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::Z))
		{
			m_Position.y -= m_TranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::Q))
		{
			m_Rotation.y += m_RotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::E))
		{
			m_Rotation.y -= m_RotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::R))
		{
			m_Rotation.x += m_RotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::F))
		{
			m_Rotation.x -= m_RotationSpeed * ts;
		}

		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_Rotation);
	}

	bool CameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_Camera.SetViewportSize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}
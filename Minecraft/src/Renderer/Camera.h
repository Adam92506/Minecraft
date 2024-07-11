#pragma once

#include <glm/glm.hpp>

namespace Minecraft
{

	class Camera
	{
	public:
		Camera();
		Camera(const glm::vec3& position, const glm::vec3& rotation, float viewportWidth, float viewportHeight);

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width, m_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjection() const { return m_Projection; }
		glm::mat4 GetViewProjection() const { return m_ViewMatrix * m_Projection; }

		glm::quat GetOrientation() const;

		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateView(); }
		void OffsetPosition(const glm::vec3& offset) { m_Position += offset; UpdateView(); }
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; UpdateView(); }
		void OffsetRotation(const glm::vec3& offset) { m_Rotation += offset; UpdateView(); }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		void SetFOV(float fov) { m_FOV = fov; UpdateProjection(); }
		float GetFOV() const { return m_FOV; }
	private:
		void UpdateProjection();
		void UpdateView();
	private:
		float m_FOV = 70.0f;
		float m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f }; // Degrees

		float m_AspectRatio = 1.778f;
		float m_ViewportWidth = 1920.0f, m_ViewportHeight = 1080.0f;
	};

}
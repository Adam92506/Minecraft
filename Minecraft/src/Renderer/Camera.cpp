#include "pch.h"
#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Minecraft
{

	Camera::Camera()
	{
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);

		UpdateView();
	}

	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, float viewportWidth, float viewportHeight)
		: m_Position(position), m_Rotation(rotation), m_AspectRatio(viewportWidth / viewportHeight), m_ViewportWidth(viewportWidth), m_ViewportHeight(viewportHeight)
	{
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);

		UpdateView();
	}

	void Camera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void Camera::UpdateView()
	{
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	glm::quat Camera::GetOrientation() const
	{
		return glm::quat(glm::radians(m_Rotation));
	}


}
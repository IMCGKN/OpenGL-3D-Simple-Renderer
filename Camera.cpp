#include "Camera.h"

void Camera::UpdateCamera(Window& window, Shader& shader)
{
	window.GetMousePos(&mouseX, &mouseY);
	if (window.IsKeyPressed(GLFW_KEY_W))
		cameraPos += cameraSpeed * cameraFront * window.GetDeltaTime();
	if (window.IsKeyPressed(GLFW_KEY_S))
		cameraPos -= cameraSpeed * cameraFront * window.GetDeltaTime();
	if (window.IsKeyPressed(GLFW_KEY_A))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * window.GetDeltaTime();
	if (window.IsKeyPressed(GLFW_KEY_D))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * window.GetDeltaTime();

	if (firstMouse)
	{
		lastX = mouseX;
		lastY = mouseY;
		firstMouse = false;
	}

	float xOffset = mouseX - lastX;
	float yOffset = lastY - mouseY;
	lastX = mouseX;
	lastY = mouseY;

	xOffset *= cameraRotSpeed * window.GetDeltaTime();
	yOffset *= cameraRotSpeed * window.GetDeltaTime();

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.Use();
	shader.SetMat4("View", view);
	shader.Unuse();
}

float Camera::GetFov() const
{
	return fov;
}

float Camera::GetFar() const
{
	return far;
}

float Camera::GetNear() const
{
	return near;
}

glm::vec3 Camera::getPos() const
{
	return cameraPos;
}
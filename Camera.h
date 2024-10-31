#pragma once

#include "Prerequisites.h"

#include "Window.h"
#include "Shader.h"

class Camera
{
public:
	void UpdateCamera(Window& window, Shader& shader);

	float GetFov() const;
	float GetFar() const;
	float GetNear() const;
	
	glm::vec3 getPos() const;
private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	double mouseX = 0.0, mouseY = 0.0f;

	float cameraSpeed = 10.0f;
	float cameraRotSpeed = 200.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400.0f, lastY = 300.0f;
	float fov = 60.0f;
	float near = 0.01f;
	float far = 100.0f;

	bool firstMouse = true;
};

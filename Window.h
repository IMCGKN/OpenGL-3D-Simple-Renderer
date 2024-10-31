#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
	void Init(int w, int h, const std::string& title);
	void Destroy();
	void GetMousePos(double* x, double* y);
	void SwapBuffers();
	void Input();
	void CalculateDeltaTime();

	float GetAspectRatio() const;
	float GetDeltaTime() const;

	int GetWidth() const;
	int GetHeight() const;

	bool IsOpen() const;
	bool IsKeyPressed(int key) const;
	
private:
	GLFWwindow* window = nullptr;

	int width = 0;
	int height = 0;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

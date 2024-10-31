#pragma once

#include <iostream>

#include "Camera.h"
#include "GameObject.h"
#include "Prerequisites.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

class Application
{
public:
	void Init()
	{
		window.Init(1280, 780, "OpenGL Nauka");
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
		
		glGenFramebuffers(1, &framebufferId);
		
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		mainShader.Init("main.vert", "main.frag");
		lightShader.Init("light.vert", "light.frag");

		mainTexture.Init("container.jpg", GL_RGB);
		soilTexture.Init("soil.jpg", GL_RGB);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.GetFov()), window.GetAspectRatio(), camera.GetNear(), camera.GetFar());
		mainShader.Use();
		mainShader.SetInt("tex0", 0);
		mainShader.SetMat4("Projection", projection);
		mainShader.Unuse();
		lightShader.Use();
		mainShader.SetMat4("Projection", projection);
		lightShader.Unuse();

		std::vector<Vertex> verticesNormal = {
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 4  LEFT
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 0  LEFT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 3  LEFT
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 4  LEFT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 3  LEFT
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, // 7  LEFT

			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 0  FRONT
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 1  FRONT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 2  FRONT
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 0  FRONT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 2  FRONT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, 0.0f, 1.0f) }, // 3  FRONT

			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 1  RIGHT
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 5  RIGHT
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 6  RIGHT
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 1  RIGHT
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 6  RIGHT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f, 0.0f, 0.0f) }, // 2  RIGHT

			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 6  BACK
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 5  BACK
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 4  BACK
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 7  BACK
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 6  BACK
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 0.0f,-1.0f) }, // 4  BACK

			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 3  TOP
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 2  TOP
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 6  TOP
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 3  TOP
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 6  TOP
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, 1.0f, 0.0f) }, // 7  TOP

			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 4  BOTTOM
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 5  BOTTOM
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 1  BOTTOM
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 4  BOTTOM
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 1  BOTTOM
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,-1.0f, 0.0f) }, // 0  BOTTOM
		};
		std::vector<VertexLight> verticesLight = {
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  LEFT
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 0  LEFT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3  LEFT
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  LEFT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3  LEFT
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 7  LEFT

			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 0  FRONT
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 1  FRONT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 2  FRONT
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 0  FRONT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 2  FRONT
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3  FRONT

			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 1  RIGHT
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 5  RIGHT
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  RIGHT
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 1  RIGHT
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  RIGHT
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 2  RIGHT

			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  BACK
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 5  BACK
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  BACK
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 7  BACK
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  BACK
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  BACK

			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3  TOP
			{ glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 2  TOP
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  TOP
			{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3  TOP
			{ glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 6  TOP
			{ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 7  TOP

			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  BOTTOM
			{ glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 5  BOTTOM
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 1  BOTTOM
			{ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 4  BOTTOM
			{ glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 1  BOTTOM
			{ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 0  BOTTOM
		};
		cube1 = GameObject::createGameObject(verticesNormal, {}, { 0.0f, 3.0f, 3.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		cube2 = GameObject::createGameObject(verticesNormal, {}, { 1.0f, 5.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		cube3 = GameObject::createGameObject(verticesNormal, {}, { 5.0f, 8.0f, -2.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		cube4 = GameObject::createGameObject(verticesNormal, {}, { 1.0f, 4.0f, -12.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		cube5 = GameObject::createGameObject(verticesNormal, {}, { 0.0f, 6.0f, 3.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		light = GameObject::createGameObject(verticesLight, {}, { -4.0f, 0.0f, 0.0f }, { 0.3f, 0.3f, 0.3f }, { 0.0f, 0.0f, 0.0f });
		ground = GameObject::createGameObject(verticesNormal, {}, { 0.0f, -8.0f, 0.0f }, { 37.0f, 1.0f, 37.0f }, { 0.0f, 0.0f, 0.0f });

		MainLoop();
	}

private:
	void MainLoop()
	{
		while (window.IsOpen())
		{
			float radius = 12.0f;
			float angle = glfwGetTime() * 4.0f;
			float x = -10.0f + cos(angle) * radius;
			float y = 5.0f + sin(angle) * radius;
			float z = -8.0f + sin(angle) * radius;
			light.SetPosition({ x, y, z });
			// Update
			window.CalculateDeltaTime();
			window.Input();

			camera.UpdateCamera(window, mainShader);
			camera.UpdateCamera(window, lightShader);

			mainShader.Use();
			mainShader.SetVec3("lightPos", light.getPos());
			mainShader.SetVec3("viewPos", camera.getPos());
			mainShader.Unuse();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.06f, 0.06f, 0.06f, 1.0f);

			mainTexture.Use();
			cube1.Render(mainShader, window);
			cube2.Render(mainShader, window);
			cube3.Render(mainShader, window);
			cube4.Render(mainShader, window);
			cube5.Render(mainShader, window);
			mainTexture.Unuse();

			soilTexture.Use();
			ground.Render(mainShader, window);
			soilTexture.Unuse();

			light.Render(lightShader, window);

			window.SwapBuffers();
		}

		Destroy();
	}

	void Destroy()
	{
		window.Destroy();
	}

private:
	Window window;
	Shader mainShader;
	Shader lightShader;
	Texture mainTexture;
	Texture soilTexture;
	GameObject cube1;
	GameObject cube2;
	GameObject cube3;
	GameObject cube4;
	GameObject cube5;
	GameObject ground;
	GameObject light;

	Camera camera;
	const unsigned int SHADOW_WIDTH = 1024;
	const unsigned int SHADOW_HEIGHT = 1024;

	unsigned int framebufferId = 0;
	unsigned int depthMap = 0;
};

#pragma once

#include <vector>

#include "Prerequisites.h"

#include "Shader.h"
#include "Window.h"

using id_t = unsigned int;

static id_t lastId = 0;

class GameObject
{
public:
	static GameObject createGameObject(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation) {
		static id_t currentId = 0;
		GameObject obj{};
		obj.Init(currentId++, vertices, indices, position, scale, rotation);
		lastId = currentId;
		return obj;
	}

	static GameObject createGameObject(const std::vector<VertexLight>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation) {
		GameObject obj{};
		obj.Init(lastId++, vertices, indices, position, scale, rotation);
		return obj;
	}

	void Render(Shader& shader, Window& window);

	void SetRotation(float rotSpeed, const glm::vec3& rot);
	void SetPosition(const glm::vec3& pos);

	glm::vec3 getPos() const;
	id_t getId() const
	{
		return ID;
	}
private:
	void Init(id_t gameObjId, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);
	void Init(id_t gameObjId, const std::vector<VertexLight>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);

private:
	id_t ID;

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;

	int indicesSize = 0;
	int verticesSize = 0;
	float angle = 0.0f;
	float rotationSpeed = 100.0f;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	float width = 0.0f, length = 0.0f, height = 0.0f;
};

#include "GameObject.h"

void GameObject::Init(id_t gameObjId, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
{
	ID = gameObjId;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	indicesSize = indices.size();
	verticesSize = vertices.size();

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void GameObject::Init(id_t gameObjId, const std::vector<VertexLight>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
{
	ID = gameObjId;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	indicesSize = indices.size();
	verticesSize = vertices.size();

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexLight), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLight), (const void*)offsetof(VertexLight, Position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLight), (const void*)offsetof(VertexLight, Color));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void GameObject::Render(Shader& shader, Window& window)
{
	if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0)
		angle += rotationSpeed * window.GetDeltaTime();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);

	if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0)
		model = glm::rotate(model, glm::radians(angle), rotation);

	shader.Use();
	shader.SetMat4("Model", model);
	glBindVertexArray(vao);
	if (indicesSize != 0)
	{
		glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, verticesSize);
	}
	shader.Unuse();
	glBindVertexArray(0);
}

void GameObject::SetRotation(float rotSpeed, const glm::vec3& rot)
{
	rotationSpeed = rotSpeed;
	rotation = rot;
}

void GameObject::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

glm::vec3 GameObject::getPos() const
{
	return position;
}
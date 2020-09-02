#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(std::vector<glm::vec3> vertexs, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs)
{
	this->vertexs = vertexs;
	this->normals = normals;
	this->uvs = uvs;

	InitMesh();
}

GLsizei Mesh::Size()
{
	return this->vertexs.size() * sizeof(glm::vec3);
}

void Mesh::InitMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	GLuint vbuffer;
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexs.size() * sizeof(glm::vec3), &this->vertexs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	if (!this->normals.empty())
	{
		GLuint nbuffer;
		glGenBuffers(1, &nbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(1);
	}

	if (!this->uvs.empty())
	{
		GLuint uvbuffer;
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(2);
	}
}

void Mesh::Render()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, Size());
	glBindVertexArray(0);
}
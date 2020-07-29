#pragma once
#include "Global.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	Mesh(std::vector<glm::vec3> vertexs, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs);

	GLsizei Size();
	void Render();
	GLuint GetVAO();
private:
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	GLuint vao;

	void InitMesh();
};
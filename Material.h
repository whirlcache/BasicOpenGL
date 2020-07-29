#pragma once
#include "Global.h"
#include "Shader.h"

class Material
{
public:
	Material();
	Material(Shader shader);
	~Material();

	void SetMat4(const GLchar*, glm::mat4);
	void SetVec3(const GLchar*, glm::vec3);
	void Render();

	void SetTexture(const GLchar* src);

private:
	Shader shader;
	GLuint texture;
};
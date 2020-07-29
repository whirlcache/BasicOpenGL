#pragma once
#include "Global.h"

class Shader
{
public:
	Shader();
	Shader(string , string);
	~Shader();

	void SetMat4(const GLchar*, glm::mat4);
	void SetVec3(const GLchar*, float, float, float);
	void SetVec3(const GLchar*, glm::vec3);
	void SetInt(const GLchar*, int);
	void SetFloat(const GLchar*, float);
	void UseProgram();

private:
	GLuint shaderProgram;
};


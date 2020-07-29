#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Material.h"

Material::Material()
{

}
Material::~Material()
{

}

Material::Material(Shader shader)
{
	this->shader = shader;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
}

void Material::SetVec3(const GLchar* propStr, glm::vec3 vec3)
{
	this->shader.UseProgram();
	this->shader.SetVec3(propStr, vec3);
}
void Material::SetMat4(const GLchar* propStr, glm::mat4 mat4)
{
	this->shader.UseProgram();
	this->shader.SetMat4(propStr, mat4);
}
void Material::SetTexture(const GLchar* src)
{
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(GL_TRUE);

	int imgWidth, imgHeight, imgChannel;
	unsigned char* imgData = stbi_load(src, &imgWidth, &imgHeight, &imgChannel, 0);
	if (imgData)
	{
		if (imgChannel == 4)
		{//RGBA 4 channel
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		}
		else
		{//RGB 3 channel
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Image File not found!" << endl;
	}
	stbi_image_free(imgData);

	this->shader.UseProgram();
	this->shader.SetInt("outTexture", 0);
}


void Material::Render()
{
	this->shader.UseProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}
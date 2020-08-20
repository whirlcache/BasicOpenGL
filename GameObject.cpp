#include "GameObject.h"

GameObject::GameObject(Mesh mesh, Material matrials)
{
	this->material = matrials;
	this->mesh = mesh;
}

GameObject::~GameObject()
{

}

void GameObject::UpdateMaterialInt(const GLchar* prop, int value)
{
	this->material.SetInt(prop, value);
}

void GameObject::UpdateMaterialMat4(const GLchar* prop, glm::mat4 mat4)
{
	this->material.SetMat4(prop, mat4);
}

void GameObject::UpdateMaterialVec3(const GLchar* prop, glm::vec3 vec3)
{
	this->material.SetVec3(prop, vec3);
}

void GameObject::SetTexture(const GLchar* src)
{
	this->material.SetTexture(src);
}

void GameObject::Render()
{
	this->material.Render();
	this->mesh.Render();
}
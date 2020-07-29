#include "GameObject.h"

GameObject::GameObject(Mesh mesh, Material matrials)
{
	this->material = matrials;
	this->mesh = mesh;
}

GameObject::~GameObject()
{

}

void GameObject::UpdateMaterialMat4(const char* prop, glm::mat4 mat4)
{
	this->material.SetMat4(prop, mat4);
}

void GameObject::UpdateMaterialVec3(const char* prop, glm::vec3 vec3)
{
	this->material.SetVec3(prop, vec3);
}

void GameObject::Render()
{
	this->mesh.Render();
	this->material.Render();
}
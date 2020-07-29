#pragma once
#include "Mesh.h"
#include "Material.h"

class GameObject
{
public:
	GameObject(Mesh mesh, Material material);
	~GameObject();

	void UpdateMaterialMat4(const char* prop, glm::mat4);
	void UpdateMaterialVec3(const char* prop, glm::vec3);
	void Render();

private:
	Mesh mesh;
	Material material;
};
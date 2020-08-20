#pragma once
#include "Mesh.h"
#include "Material.h"

class GameObject
{
public:
	GameObject(Mesh mesh, Material material);
	~GameObject();

	void UpdateMaterialInt(const GLchar* prop, int);
	void UpdateMaterialMat4(const GLchar* prop, glm::mat4);
	void UpdateMaterialVec3(const GLchar* prop, glm::vec3);
	void Render();
	void SetTexture(const GLchar* src);

private:
	Mesh mesh;
	Material material;
};
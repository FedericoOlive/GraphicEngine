#include "Model.h"
#include <iostream>
#include "ModelImporter.h"

Model::Model(Renderer* renderer, std::string const& path, bool isInvertIndexesOrder, bool isInvertTextures)
{
	this->isInvertIndexesOrder = isInvertIndexesOrder;
	name = "Model";
	SetRenderer(renderer);
	material = new Material(renderer->GetDefaultShader(), true);

	ModelImporter::LoadModel(path, directory, meshes, textures_loaded, isInvertTextures);
}

Model::~Model() {}
void Model::CreateVertexData() {}

void Model::Draw(Camera* camera)
{
	if (isInvertIndexesOrder) 
		glFrontFace(GL_CW);
	renderer->DrawModel(transform->GetModelMatrix(), NULL, material, alpha, camera, meshes);
	if (isInvertIndexesOrder)
		glFrontFace(GL_CCW);
}

void Model::GenBufferEntity() {}

void Model::BindBufferEntity() {}

void Model::RecalculateAABB()
{
	if (meshes.size() > 0)
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			Mesh* mesh = &meshes[i];
			for (int j = 0; j < mesh->vertices.size(); j++)
			{
				Vertex vertex = mesh->vertices[j];

				transform->aabb->min.x = glm::min(transform->aabb->min.x, vertex.Position.x);
				transform->aabb->min.y = glm::min(transform->aabb->min.y, vertex.Position.y);
				transform->aabb->min.z = glm::min(transform->aabb->min.z, vertex.Position.z);
				transform->aabb->max.x = glm::max(transform->aabb->max.x, vertex.Position.x);
				transform->aabb->max.y = glm::max(transform->aabb->max.y, vertex.Position.y);
				transform->aabb->max.z = glm::max(transform->aabb->max.z, vertex.Position.z);
			}
		}
	}
	
	CalculateParentAABB();
}
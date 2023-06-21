#include "Model.h"
#include <iostream>

Model::Model(Renderer* renderer, std::string const& path, bool isInvertIndexesOrder, bool isInvertTextures)
{
	this->isInvertIndexesOrder = isInvertIndexesOrder;
	name = "Model";
	SetRenderer(renderer);
	material = new Material(renderer->GetDefaultShader(), true);

	ModelImporter::LoadModel(path, directory, meshes, textures_loaded, isInvertTextures, m_BoneInfoMap, m_BoneCounter);
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

void Model::OnAsigned()
{
	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
	RecalculateAABB();
}

void Model::RecalculateAABB()
{
	transform->aabb->BeforeUpdate();
	
	if (meshes.size() > 0)
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			Mesh* mesh = &meshes[i];
			for (int j = 0; j < mesh->vertices.size(); j++)
			{
				Vertex vertex = mesh->vertices[j];
				glm::vec3 modelVertex = (transform->GetModelMatrix() * glm::vec4(vertex.Position, 1.0f));
				
				transform->aabb->min.x = glm::min(transform->aabb->min.x, modelVertex.x);
				transform->aabb->min.y = glm::min(transform->aabb->min.y, modelVertex.y);
				transform->aabb->min.z = glm::min(transform->aabb->min.z, modelVertex.z);
				transform->aabb->max.x = glm::max(transform->aabb->max.x, modelVertex.x);
				transform->aabb->max.y = glm::max(transform->aabb->max.y, modelVertex.y);
				transform->aabb->max.z = glm::max(transform->aabb->max.z, modelVertex.z);
			}
		}
	}
	
	transform->aabb->AfterUpdate(gameobject->name);
	CalculateParentAABB();
}
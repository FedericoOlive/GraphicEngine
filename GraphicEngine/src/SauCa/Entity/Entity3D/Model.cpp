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

void Model::OnAsigned()
{
	std::function<void()> recalculateAABB = [this] { RecalculateAABB(); };
	transform->OnUpdateModelMatrix.AddListener(recalculateAABB);
	RecalculateAABB();
}

void Model::RecalculateAABB()
{
	transform->aabbGlobal->BeforeUpdate();
	
	if (meshes.size() > 0)
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			Mesh* mesh = &meshes[i];
			for (int j = 0; j < mesh->vertices.size(); j++)
			{
				Vertex vertex = mesh->vertices[j];
				glm::vec3 modelVertex = (transform->GetModelMatrix() * glm::vec4(vertex.Position, 1.0f));
				
				transform->aabbGlobal->min.x = glm::min(transform->aabbGlobal->min.x, modelVertex.x);
				transform->aabbGlobal->min.y = glm::min(transform->aabbGlobal->min.y, modelVertex.y);
				transform->aabbGlobal->min.z = glm::min(transform->aabbGlobal->min.z, modelVertex.z);
				transform->aabbGlobal->max.x = glm::max(transform->aabbGlobal->max.x, modelVertex.x);
				transform->aabbGlobal->max.y = glm::max(transform->aabbGlobal->max.y, modelVertex.y);
				transform->aabbGlobal->max.z = glm::max(transform->aabbGlobal->max.z, modelVertex.z);
			}
		}
	}
	
	transform->aabbGlobal->AfterUpdate();

	transform->aabbLocal->min = transform->aabbGlobal->min;
	transform->aabbLocal->max = transform->aabbGlobal->max;
	transform->aabbLocal->AfterUpdate();

	CalculateParentAABB();
}
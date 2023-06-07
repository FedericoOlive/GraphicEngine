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


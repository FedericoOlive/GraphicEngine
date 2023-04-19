#ifndef VERTEX_H
#define VERTEX_H
#include "Exports.h"

class SAUCA_API VertexData
{
public:
	~VertexData();
	
	unsigned int VAO;

	unsigned int VBO;
	const int atribVertex = 0;
	const int atribVertexSize = 3;
	int sizeVertices;
	float* vertices;
	
	unsigned int COL;
	const int atribColor = 1;
	const int atribColorSize = 3;
	int sizeColor;
	float* colors;
	
	unsigned int LVAO;
	const int atribNormal = 2;
	const int atribNormalSize = 3;
	int sizeNormals;
	float* normals;
	
	unsigned int UVB;
	const int atribUvs = 3;
	const int atribUvsSize = 2;
	int sizeUvs;
	float* uvs;
	
	unsigned int EBO;
	int sizeIndex;
	int* indexes;
};

#endif
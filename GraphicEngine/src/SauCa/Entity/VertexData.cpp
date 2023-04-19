#include "VertexData.h"

VertexData::~VertexData()
{
	delete vertices;
	delete colors;
	delete normals;
	delete uvs;
	delete indexes;	
}
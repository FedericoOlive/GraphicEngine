#include "Triangle.h"

Triangle::Triangle()
{
	size = 18;
	
	vertices = new float[size] {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};


	
}

Triangle::~Triangle()
{
	delete vertices;
}
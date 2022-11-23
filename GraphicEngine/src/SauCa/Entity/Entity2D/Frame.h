#ifndef FRAME_H
#define FRAME_H

#include "Exports.h"
#include <vector>

using namespace std;

struct coordinate
{
	float u;
	float v;
};

class SAUCA_API Frame
{
	public:
		Frame();
		~Frame();
		coordinate coordinates[4];
};

#endif


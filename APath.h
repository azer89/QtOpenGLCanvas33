#ifndef APATH_H
#define APATH_H

#include "AVector.h"

#include <vector>
#include <limits>
#include <cmath>

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* March 2016
*/

struct APath
{
public:
	std::vector<AVector> points;
	bool isClosed;
	// float thickness;

	APath()
	{
		this->isClosed = false;
	}
};

#endif // APATH_H

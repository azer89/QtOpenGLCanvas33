#ifndef ATRIANGLE_H
#define ATRIANGLE_H

#include "AVector.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

struct ATriangle
{
public:
	AVector _ptA;
	AVector _ptB;
	AVector _ptC;
	//AVector _ptD;

	// Constructor #1
	ATriangle()
	{
	}

	// Constructor #2
	ATriangle(AVector ptA, AVector ptB, AVector ptC)
	{
		this->_ptA = ptA;
		this->_ptB = ptB;
		this->_ptC = ptC;
	}
};

#endif // ATRIANGLE_H

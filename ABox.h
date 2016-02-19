#ifndef ABOX_H
#define ABOX_H

#include "AVector.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

struct ABox
{
public:
	AVector _ptA;
	AVector _ptB;
	AVector _ptC;
	AVector _ptD;

	// Constructor #1
	ABox()
	{
	}

	// Constructor #2
	ABox(AVector ptA, AVector ptB, AVector ptC, AVector ptD)
	{
		this->_ptA = ptA;
		this->_ptB = ptB;
		this->_ptC = ptC;
		this->_ptD = ptD;
	}
};

#endif // ABOX_H

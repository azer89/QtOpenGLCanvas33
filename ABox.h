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
	/* I know these are not the most compact representation
	but whatever... */
	AVector _ptA; // topleft
	AVector _ptB; // topright
	AVector _ptC; // downleft
	AVector _ptD; // downright

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

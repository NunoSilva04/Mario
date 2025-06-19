#ifndef ID3D_H_
#define ID3D_H_

#include "AllHeaderFiles.h"

class Id3d {
public:
	Id3d();
	~Id3d();
	static Id3d* createInstance();
	virtual ID3D11Device* getDevice() = 0;
};

#endif // !ID3D_H_

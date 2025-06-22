#include "Id3d.h"
#include "D3D.h"

Id3d* Id3d::createInstance(){
	return new D3D();
}
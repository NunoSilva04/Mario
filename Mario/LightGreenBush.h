#ifndef LIGHTGREENBUSH_H_
#define LIGHTGREENBUSH_H_

#include "Background.h"

class LIGHTGREENBUSH : public BACKGROUND {
public:
	LIGHTGREENBUSH();
	~LIGHTGREENBUSH();
	void initInstanceBuffer(ID3D11Device* dev) override;
	void initShaderResourceView(ID3D11Device* dev) override;
};

#endif //  LIGHTGREENBUSH_H_
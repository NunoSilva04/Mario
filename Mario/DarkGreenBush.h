#ifndef DARKGREENBUSH_H_
#define DARKGREENBUSH_H_

#include "Background.h"

class DARKGREENBUSH : public BACKGROUND {
public:
	DARKGREENBUSH();
	~DARKGREENBUSH();
	void initInstanceBuffer(ID3D11Device* dev) override;
	void initShaderResourceView(ID3D11Device* dev) override;
};

#endif // !DARKGREENBUSH_H_
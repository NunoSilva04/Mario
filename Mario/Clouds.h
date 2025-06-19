#ifndef CLOUDS_H_
#define CLOUDS_H_

#include "Background.h"

class CLOUDS : public BACKGROUND {
public:
	CLOUDS();
	~CLOUDS();
	void initInstanceBuffer(ID3D11Device* dev) override;
	void initShaderResourceView(ID3D11Device* dev) override;
};

#endif // !CLOUDS_H_
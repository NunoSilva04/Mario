#ifndef FLAG_G_
#define FLAG_G_

#include "Background.h"

class Flag : public BACKGROUND {
public:
	Flag();
	~Flag();
	void initInstanceBuffer(ID3D11Device* dev) override;
	void initShaderResourceView(ID3D11Device* dev) override;
};

#endif // !FLAG_G_
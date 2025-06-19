#ifndef UNBREAKABLEBRICK_H_
#define UNBREAKABLEBRICK_H_

#include "Block.h"

class UnbreakableBrick : public Block {
public:
	UnbreakableBrick();
	~UnbreakableBrick() override;

private:
	void initInstanceBuffer(ID3D11Device* dev) override;
	const Microsoft::WRL::ComPtr<ID3D11Buffer> getInstanceBuffer() const override;
	const UINT getSizeofInstanceStruct() const override;
	const int getNumBlockTypeInstances() override;
	const int getNumBlockTypeInstancesToRender() const override;
	const DirectX::XMFLOAT3 getInstanceVertice(int ID, int verticeNumber) override;
	void resetInstances() override;
	void addIstance(int instanceID) override;
	void updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) override;
	void getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const override;

	Microsoft::WRL::ComPtr<ID3D11Buffer> instanceBuffer;

	struct instanceStruct {
		DirectX::XMMATRIX transformMatrix;
		DirectX::XMFLOAT2 newUVValues[4];
		int instanceID;
		DirectX::XMFLOAT3 verticesPos[4];
	};
	std::vector<instanceStruct> instances, initNumInstances, instancesToRender;
};

#endif // !UNBREAKABLEBRICK_H_

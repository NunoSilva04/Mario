#ifndef BLOCK_H_
#define BLOCK_H_

#include "AllHeaderFiles.h"
#include <wrl/client.h>
#include "IGameObjects.h"
#include "GameObjects.h"

enum class BlockType {
	FloorTile,
	DarkFloorTile,
	Brick,
	DarkBrick,
	MysteryBlock,
	UnbreakableBrick,
	Pipe,
};

class Block : public GameObjects, public IGameObjects {
public:
	Block();
	~Block();
	static std::shared_ptr<GameObjects> createBlockType(const std::string specificType);
	void initObject(ID3D11Device* dev) override;
	void updateObject(ID3D11DeviceContext* devCon, std::shared_ptr<IGrid> const IGridsToUse) override;
	void renderObject(ID3D11DeviceContext* devCon) override;

private:
	void initBlockShaders(ID3D11Device* dev);
	void initBlockVertexBuffer(ID3D11Device* dev);
	void initBlockIndexBuffer(ID3D11Device* dev);
	void initBlockShaderResourceView(ID3D11Device* dev);

	static Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	static Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	static Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	struct vertexStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	};

	static bool hasShader, hasVertexBuffer, hasIndexBuffer, hasSRV;
	static std::vector<std::shared_ptr<Block>> allBlockArray;

	int getNumObjectSubType() const override;
	int getObjectSubTypeNumInstances(int currObjectSubType) const override;
	void getObjectSubTypePosition(int currObjectSubType, DirectX::XMFLOAT3* positions, int currInstance) const override;

protected:
	virtual void initInstanceBuffer(ID3D11Device* dev) = 0;
	virtual const Microsoft::WRL::ComPtr<ID3D11Buffer> getInstanceBuffer() const = 0;
	virtual const UINT getSizeofInstanceStruct() const = 0;
	virtual const int getNumBlockTypeInstances() = 0;
	virtual const int getNumBlockTypeInstancesToRender() const = 0;
	virtual const DirectX::XMFLOAT3 getInstanceVertice(int ID, int verticeNumber) = 0;
	virtual void resetInstances() = 0;
	virtual void addIstance(int instanceID) = 0;
	virtual void updateBlockTypeInstanceBuffer(ID3D11DeviceContext* devCon) = 0;
	virtual void getVerticesPosition(DirectX::XMFLOAT3* positions, int currInstance) const = 0;
};

#endif // !BLOCK_H_
#ifndef OPTIONCURSOR_H_
#define OPTIONCURSOR_H_

#include "AllHeaderFiles.h"

class OPTIONCURSOR {
public:
	static OPTIONCURSOR& getInstance() {
		static OPTIONCURSOR instance;
		return instance;
	}

	void initOptionCursor(ID3D11Device* dev);
	void initOptionCursorShaders(ID3D11Device* dev);
	void initOptionCursorVertexBuffer(ID3D11Device* dev);
	void initOptionCursorIndexBuffer(ID3D11Device* dev);
	void initOptionCursorShaderResourceView(ID3D11Device* dev);
	void updateOptionCursor(float frame_time);
	void renderOptionCursor(ID3D11DeviceContext* devCon);
	void cleanOptionCursor();
	int state;

private:
	OPTIONCURSOR();
	~OPTIONCURSOR();
	OPTIONCURSOR(const OPTIONCURSOR&) = delete;
	OPTIONCURSOR& operator =(const OPTIONCURSOR&) = delete;

	ID3D11VertexShader* optionCursorVertexShader;
	ID3D11PixelShader* optionCursorPixelShader;
	ID3D11InputLayout* optionCursorInputLayout;
	ID3D11Buffer* optionCursorVertexBuffer;
	ID3D11Buffer* optionCursorIndexBuffer;
	ID3D11ShaderResourceView* optionCursorShaderResourceView;
	ID3D11SamplerState* optionCursorSamplerState;
	DirectX::XMMATRIX optionCursorWorld;
	float translationY, coolDown;

	struct optionCursorStruct {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
	};
	optionCursorStruct optionCursorVertices[4];
};

#endif // !OPTIONCURSOR_H_
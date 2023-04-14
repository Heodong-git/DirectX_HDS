#pragma once
#include <GameEngineBase/GameEngineMath.h>



// D3D11_INPUT_ELEMENT_DESC

class GameEngineInputLayOut
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;

public:
	void AddInputLayOut(
		LPCSTR SemanticName,  // ������ �ǹ�
		DXGI_FORMAT Format,   // �� ������ �ڷ���
		D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��°� ǥ��
		UINT InstanceDataStepRate = 0, // �ν��Ͻ��̶�� ������ ��� �� ����ϰ� �� ��
		UINT AlignedByteOffset = -1,   // 0��° ����Ʈ���� 
		UINT InputSlot = 0, // �������� ���۸� ������ ��� N��° ������ ���̾ƿ��̴� ��� ���� �˷��ٶ� ���
		UINT SemanticIndex = 0
	);

};

class GameEngineVertex
{
public:
	static GameEngineInputLayOut LayOut;

public:
	float4 POSITION; // 0 16
	float4 COLOR;    // 16 32
};


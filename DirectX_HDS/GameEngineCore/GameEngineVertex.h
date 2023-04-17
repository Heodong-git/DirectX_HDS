#pragma once
#include <GameEngineBase/GameEngineMath.h>

class GameEngineInputLayOutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs()
	{
		return Descs;
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	int Offset = 0;

public:
	void AddInputLayOut(
		LPCSTR SemanticName,  // 변수의 의미
		DXGI_FORMAT Format,   // 그 변수의 자료형
		D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현
		UINT InstanceDataStepRate = 0, // 인스턴싱이라는 구조를 배울 때 사용하게 될 것
		UINT AlignedByteOffset = -1,   // 0번째 바이트부터 
		UINT InputSlot = 0, // 여러개의 버퍼를 세팅할 경우 N번째 버퍼의 레이아웃이다 라는 것을 알려줄때 사용
		UINT SemanticIndex = 0
	);

};

class GameEngineVertex
{
public:
	static GameEngineInputLayOutInfo LayOut;

public:
	float4 POSITION; // 0 16
	float4 COLOR;    // 16 32
};


#include "PrecompileHeader.h"
#include "GameEngineVertex.h"


void GameEngineInputLayOut::AddInputLayOut(
	LPCSTR SemanticName, 
	DXGI_FORMAT Format,  
	D3D11_INPUT_CLASSIFICATION InputSlotClass, // 버텍스 데이터가 인스턴싱 데이터다 라는 것을 표현
	UINT InstanceDataStepRate, 
	UINT AlignedByteOffset, 
	UINT InputSlot, 
	UINT SemanticIndex 
)
{
	D3D11_INPUT_ELEMENT_DESC Data;
	// POSITION
	Data.SemanticName = SemanticName;
	Descs.push_back(Data);
}

GameEngineInputLayOut GameEngineVertex::LayOut;
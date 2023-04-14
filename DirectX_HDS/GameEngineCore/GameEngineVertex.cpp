#include "PrecompileHeader.h"
#include "GameEngineVertex.h"


void GameEngineInputLayOut::AddInputLayOut(
	LPCSTR SemanticName, 
	DXGI_FORMAT Format,  
	D3D11_INPUT_CLASSIFICATION InputSlotClass, // ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��� ���� ǥ��
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
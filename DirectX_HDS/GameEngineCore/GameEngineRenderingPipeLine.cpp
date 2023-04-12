#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// 매쉬 + 머티리얼

// 점에 대한 정보를 준비하고
void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBuffer)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBuffer->Setting();
	// GameEngineDevice::GetContext()->IASetVertexBuffers()
}
// 로컬에 존재하는 점을 우리가 만든 행렬을 통해서 변환하고.
void GameEngineRenderingPipeLine::VertexShader()
{
	// GameEngineDevice::GetContext()->VSSetShader
}

// 점의 정보를 토대로 어떤 순서로 그릴지 정하고
void GameEngineRenderingPipeLine::InputAssembler2()
{
	// GameEngineDevice::GetContext()->IASetIndexBuffer
}

// w나누기를 해줍니다. 
// 뷰포트도 곱해줍니다.
// 화면 컬링 
// 픽셀 건지기
void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}


void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// GameEngineDevice::GetContext()->OMSetRenderTargets
}


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBuffer = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBuffer)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}

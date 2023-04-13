#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// 매쉬 + 머티리얼

// (Vertex) 정점에 대한 정보를 준비한다.
void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBufferPtr->Setting();
	// GameEngineDevice::GetContext()->IASetVertexBuffers()
}

// 각 정점(Vertex)에 대한 연산수행 
// InputAssembler 단계에서 출력되는 premitive 의 각 vertex에 대한 연산 수행
// 모든 정점들에 대해서 한번씩 실행되고 각 정점마다 한번만 호출된다. ****** 매우중요
// 가상의 3D 공간에 있는 꼭지점(vertex)들의 위치를 2차원 화면의 좌표로 변환하는 작업
// Transform , skinning , vertex lighting 등의 특수 효과를 수행할 수 있다. 
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않아서 버텍스 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	VertexShaderPtr->Setting();
	// GameEngineDevice::GetContext()->VSSetShader
}

// 점의 정보를 토대로 어떤 순서로 그릴지 정하고*
// 응용프로그램에서 제공 받은 정점 버퍼의 데이터를 다른 파이프라인 단계에서 사용할 프리미티브로 조립한다. 
// 메모리에서 기하자료 (index , vertex data) 를 읽어서 기하학적 기본도형을 조립한다. 
// 프리미티브 : 프로그래밍에서의 어떤 프로그램을 만드는데 사용할 수 있는 언어의 가장 기본적인 단위 문자,숫자, 요소 등
// 정점이란 : 공간적위치, 위치 값 이외의 정보를 담고 있으며 이를 통해 좀더 복잡한 렌더링 효과를 구현할 수 있다. 
void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("인덱스 버퍼가 존재하지 않아서 인풋 어셈블러2 과정을 실행할 수 없습니다.");
		return;
	}

	IndexBufferPtr->Setting();
}

// 여기서부터
void GameEngineRenderingPipeLine::HullShader()
{

}
void GameEngineRenderingPipeLine::Tessellator()
{

}
void GameEngineRenderingPipeLine::DomainShader()
{

}
void GameEngineRenderingPipeLine::GeometryShaeder()
{

}
// 여기까지는 화면과는 사실

// w나누기를 해줍니다. 
// 뷰포트도 곱해줍니다.
// 화면 컬링 
// 픽셀 건지기

// 1.원근투영 나누기 
// 2.카메라 범위를 벗어나는 pixel 잘라내기(보이지않는 프리미티브 제거) (화면컬링?)
// 3.좌표의 viewport 전환 ( 뷰포트곱 ) 
// 4.모든 픽셀들에 대해 픽셀쉐이더 호출 (픽셀건지기?)
void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}

// 각 Pixel의 데이터를 생성한다. 
// 상수변수, 텍스쳐데이터 또는 픽셀출력 데이터를 결합해 출력 색상을 결정한다. 
// 이 단계에서 픽셀조명계산 또는 픽셀에 대한 후처리를 할 수 있다. 
void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}

// 픽셀세이더에서 출력된 픽셀값을 렌더 타겟에 쓰는 작업을 수행
void GameEngineRenderingPipeLine::OutputMerger()
{
	// GameEngineDevice::GetContext()->OMSetRenderTargets
}


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}


void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다.");
	}
}

// 매쉬 + 머티리얼
void GameEngineRenderingPipeLine::Render()
{
	// 렌더링은 렌더링 파이프라인을 한바퀴 돌리는 것을 말한다. 
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	HullShader();
	Tessellator();
	DomainShader();
	GeometryShaeder();
	Rasterizer();
	PixelShader();
	OutputMerger();

	// 메쉬 <= 외형이 어떻게 보일것인가.
	//         픽셀건져내기할 범위를 지정하는 Rasterizer
	//         w나누기를 하고 뷰포트를 곱해서

	// 머티리얼 <= 색깔이 어떻게 나올것인가?
	//             레스터라이저 + 픽셀쉐이더 + 버텍스 쉐이더
}
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

// �Ž� + ��Ƽ����

// (Vertex) ������ ���� ������ �غ��Ѵ�.
void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBuffer)
	{
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	VertexBuffer->Setting();
	// GameEngineDevice::GetContext()->IASetVertexBuffers()
}

// �� ����(Vertex)�� ���� ������� 
// InputAssembler �ܰ迡�� ��µǴ� premitive �� �� vertex�� ���� ���� ����
// ��� �����鿡 ���ؼ� �ѹ��� ����ǰ� �� �������� �ѹ��� ȣ��ȴ�. ****** �ſ��߿�
// ������ 3D ������ �ִ� ������(vertex)���� ��ġ�� 2���� ȭ���� ��ǥ�� ��ȯ�ϴ� �۾�
// Transform , skinning , vertex lighting ���� Ư�� ȿ���� ������ �� �ִ�. 
void GameEngineRenderingPipeLine::VertexShader()
{
	// GameEngineDevice::GetContext()->VSSetShader
}

// ���� ������ ���� � ������ �׸��� ���ϰ�
// �������α׷����� ���� ���� ���� ������ �����͸� �ٸ� ���������� �ܰ迡�� ����� ������Ƽ��� �����Ѵ�. 
// �޸𸮿��� �����ڷ� (index , vertex data) �� �о �������� �⺻������ �����Ѵ�. 
// ������Ƽ�� : ���α׷��ֿ����� � ���α׷��� ����µ� ����� �� �ִ� ����� ���� �⺻���� ���� ����,����, ��� ��
// �����̶� : ��������ġ, ��ġ �� �̿��� ������ ��� ������ �̸� ���� ���� ������ ������ ȿ���� ������ �� �ִ�. 
void GameEngineRenderingPipeLine::InputAssembler2()
{
	// GameEngineDevice::GetContext()->IASetIndexBuffer
}

// w�����⸦ ���ݴϴ�. 
// ����Ʈ�� �����ݴϴ�.
// ȭ�� �ø� 
// �ȼ� ������

// 1.�������� ������ 
// 2.ī�޶� ������ ����� pixel �߶󳻱� 
// 3.Viewport ����
// 4.��� �ȼ��鿡 ���� �ȼ����̴� ȣ�� 
void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}

// �� Pixel�� �����͸� �����Ѵ�. 
// �������, �ؽ��ĵ����� �Ǵ� �ȼ���� �����͸� ������ ��� ������ �����Ѵ�. 
// �� �ܰ迡�� �ȼ������� �Ǵ� �ȼ��� ���� ��ó���� �� �� �ִ�. 
void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}

// �ȼ����̴����� ��µ� �ȼ����� ���� Ÿ�ٿ� ���� �۾��� ����
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
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}

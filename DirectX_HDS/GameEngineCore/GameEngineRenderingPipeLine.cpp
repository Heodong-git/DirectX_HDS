#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineDepthState.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>();
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// �Ž� + ��Ƽ����

// (Vertex) ������ ���� ������ �غ��Ѵ�.
void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == InputLayOutPtr)
	{
		MsgAssert("��ǲ ���̾ƿ��� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	InputLayOutPtr->Setting();

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	VertexBufferPtr->Setting();
	
	// 012 023 3���� ��� �Ѹ����� ������ ��� ������ ���⼭ ó��
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}

// �� ����(Vertex)�� ���� ������� 
// InputAssembler �ܰ迡�� ��µǴ� premitive �� �� vertex�� ���� ���� ����
// ��� �����鿡 ���ؼ� �ѹ��� ����ǰ� �� �������� �ѹ��� ȣ��ȴ�. ****** �ſ��߿�
// ������ 3D ������ �ִ� ����(vertex)���� ��ġ�� 2���� ȭ���� ��ǥ�� ��ȯ�ϴ� �۾� ( ��ȯ������� ) 
// Transform , skinning , vertex lighting ���� Ư�� ȿ���� ������ �� �ִ�. 
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʾƼ� ���ؽ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	VertexShaderPtr->Setting();
	// GameEngineDevice::GetContext()->VSSetShader
}

// ���� ������ ���� � ������ �׸��� ���ϰ�*
// �������α׷����� ���� ���� ���� ������ �����͸� �ٸ� ���������� �ܰ迡�� ����� ������Ƽ��� �����Ѵ�. 
// �޸𸮿��� �����ڷ� (index , vertex data) �� �о �������� �⺻������ �����Ѵ�. 
// ������Ƽ�� : ���α׷��ֿ����� � ���α׷��� ����µ� ����� �� �ִ� ����� ���� �⺻���� ���� ����,����, ��� ��
// �����̶� : ��������ġ, ��ġ �� �̿��� ������ ��� ������ �̸� ���� ���� ������ ������ ȿ���� ������ �� �ִ�. 
void GameEngineRenderingPipeLine::InputAssembler2()
{
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�ε��� ���۰� �������� �ʾƼ� ��ǲ �����2 ������ ������ �� �����ϴ�.");
		return;
	}

	IndexBufferPtr->Setting();
}

// ���⼭����
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
// ��������� ȭ����� ���

// w�����⸦ ���ݴϴ�. 
// ����Ʈ�� �����ݴϴ�.
// ȭ�� �ø� 
// �ȼ� ������

// 1.�������� ������ 
// 2.ī�޶� ������ ����� pixel �߶󳻱�(�������ʴ� ������Ƽ�� ����) (ȭ���ø�?) , ������Ƽ�긦 �ȼ������ͷ� ���� 
// 3.��ǥ�� viewport ��ȯ ( ����Ʈ�� ) 
// 4.��� �ȼ��鿡 ���� �ȼ����̴� ȣ�� (�ȼ�������?)
void GameEngineRenderingPipeLine::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�����Ͷ������� �������� �ʾƼ� ������ �Ұ����մϴ�.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();
	// GameEngineDevice::GetContext()->RSSetState
}

// �� Pixel�� �����͸� �����Ѵ�. 
// �ȼ� �����Ϳ� ���� �ؽ���ó��, ������ó���� ������ �� ���̴�������ν� �ȼ� ������ 1���� ����Ѵ�. 
// �� �ܰ迡�� �ȼ������� �Ǵ� �ȼ��� ���� ��ó���� �� �� �ִ�. 
void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʾƼ� �ȼ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	PixelShaderPtr->Setting();
	// GameEngineDevice::GetContext()->PSSetShader
}

// �ȼ����̴����� ��µ� �����ͳ� ����, ������ ���� ����Ͽ� ���������� ������ �� ���� �����Ѵ�. 
// �ȼ����̴����� ��µ� �ȼ����� ���� Ÿ�ٿ� ���� �۾��� ����
void GameEngineRenderingPipeLine::OutputMerger()
{
	if (nullptr == BlendStatePtr)
	{
		MsgAssert("���尡 �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
		return;
	}

	BlendStatePtr->Setting();
	// GameEngineDevice::GetContext()->OMSetRenderTargets

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("���尡 �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
		return;
	}

	DepthStatePtr->Setting();
}


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}

	// ���ؽ����۸� �����Ҷ� ���ؽ����̴��� ���õǾ��ִٸ� InputLayOut ���ҽ��� �����ϰ�
	// ���õǾ����� �ʴٸ� return 
	if (nullptr == VertexShaderPtr)
	{
		return;
	}

	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}


void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr == VertexBufferPtr)
	{
		return;
	}

	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�������� �ʴ� �ȼ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetBlendState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	BlendStatePtr = GameEngineBlend::Find(UpperName);

	if (nullptr == BlendStatePtr)
	{
		MsgAssert("�������� �ʴ� ���带 �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetDepthState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	DepthStatePtr = GameEngineDepthState::Find(UpperName);

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("�������� �ʴ� ���̹��� ������Ʈ�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�������� �ʴ� �����Ͷ������� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
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

	// ���� ������ �������� ���� �غ������ ������ ������ �߿����� �ʴ�. �����ϴ� �����ϻ� ������ ������������. 
}


// �Ž� + ��Ƽ����
void GameEngineRenderingPipeLine::Render()
{
	// �ε��� ���۰� ���õǾ������� �̰� ����ؼ� �׸��ǵ�
	// ������ �ε��� ���۸� ����Ұ���.
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);


	// �޽� <= ������ ��� ���ϰ��ΰ�.
	//         �ȼ����������� ������ �����ϴ� Rasterizer
	//         w�����⸦ �ϰ� ����Ʈ�� ���ؼ�

	// ��Ƽ���� <= ������ ��� ���ð��ΰ�? �޽ÿ� �����Ͽ� �ð����� ����� ������ �� �ִ� ����
	//             �����Ͷ����� + �ȼ����̴� + ���ؽ� ���̴�
}
#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"
#include "GameEngineShaderResHelper.h"

#include "GameEngineMesh.h"
#include "GameEngineBlend.h"
#include "GameEngineTexture.h"
#include "GameEngineDepthState.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexShader.h"

// ���������������ο� �ʿ��� ���ҽ� ���� �� �ε� �� ���������μ��� 
void GameEngineCore::CoreResourcesInit()
{
	// ������ �о�´�. 
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	// ���ؽ������� ����� ��ǲ���̾ƿ��� ������ �� �߿�. 
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);

	//typedef struct D3D11_INPUT_ELEMENT_DESC
	//{
	//	LPCSTR SemanticName; = "POSITION"
	//	UINT SemanticIndex; = 0
	//	DXGI_FORMAT Format; 
	//	UINT InputSlot;
	//	UINT AlignedByteOffset;
	//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	//	UINT InstanceDataStepRate; 
	//} 	
	
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	//UINT NumElements, // 
	//const void* pShaderBytecodeWithInputSignature,  // ���̴��� ���̳ʸ� �ڵ带 ����
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout // ������� ������ ������

	// ���÷��� ���� �������־���Ѵ�. 
	{
		D3D11_SAMPLER_DESC SamperData = {};

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		
		// �ؽ��İ� �ָ����� �� ������ ����� ������
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("CLAMPSAMPLER", SamperData);
	}
	{
		D3D11_SAMPLER_DESC SamperData = {};

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		
		// �ؽ��İ� �ָ����� �� ������ ����� ������
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAPSAMPLER", SamperData);
	}
	{
		// ���ؽ� �ʱ�ȭ
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// �ո�
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
	}

	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);

		// 0   1
		// 3   2
		// �ո�
		ArrVertex[0] = { { -1.0f, 1.0f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 1.0f, 1.0f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 1.0f, -1.0f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -1.0f, -1.0f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("FullRect", ArrVertex);
		GameEngineIndexBuffer::Create("FullRect", ArrIndex);

	}

	{
		// ����
		D3D11_BLEND_DESC Desc = { 0, };

		// �ڵ����� ���� �κ��� �����ؼ� ����Ѵ�. ��û����
		Desc.AlphaToCoverageEnable = false;

		// true  : ���带 ������ ���� 
		// false : 0���� ���õ� �ɷ� ��� ����
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		// ����ɼ� , + - * 
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		GameEngineBlend::Create("AlphaBlend", Desc);
	}

	{
		
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("EngineDepth", Desc);
		
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("AlwayDepth", Desc);
	}

	{
		// ��� ���� �Ⱦ�������
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// �ո�
		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		// �޸�
		ArrVertex[4] = ArrVertex[0].RotationXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotationXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotationXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotationXDegReturn(180.0f);

		// ���ʸ�
		ArrVertex[8] = ArrVertex[0].RotationYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotationYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotationYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotationYDegReturn(90.0f);

		// ������
		ArrVertex[12] = ArrVertex[0].RotationYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotationYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotationYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotationYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotationXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotationXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotationXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotationXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotationXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotationXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotationXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotationXDegReturn(-90.0f);

	}

	// ���ؽ����̴� ������
	{
		GameEngineDirectory NewDir;
		// ���ڷ� �Է��� ������ �����ϴ� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �̵�
		//NewDir.Move("katanazero_resources");
		NewDir.Move("Shader");
		// �ӽú���
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		// ���ؽ����̴��� �ȼ����̴��� ������ �ε� 
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");

		GameEngineVertexShader::Load(Files[1].GetFullPath(), "Merge_VS");
		GameEnginePixelShader::Load(Files[1].GetFullPath(), "Merge_PS");
		// �׽�Ʈ ���� 
		GameEngineVertexShader::Load(Files[2].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[2].GetFullPath(), "Texture_PS");

		GameEngineVertexShader::Load(Files[3].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[3].GetFullPath(), "Texture_PS");
		
		
		
	}

	{
		// �����Ͷ����� ����
		D3D11_RASTERIZER_DESC Desc = {};

		//D3D11_FILL_MODE FillMode;
		// �������� �� ����� ä��� ��带 �����մϴ�( D3D11_FILL_MODE ���� ).
		//D3D11_CULL_MODE CullMode;
		// ������ ������ ���ϴ� �ﰢ���� �׷����� ������ ��Ÿ���ϴ�( D3D11_CULL_MODE ���� ).
		//BOOL FrontCounterClockwise;
		// �ﰢ���� �ո����� �޸����� �����մϴ�. 
		// �� �Ű������� TRUE �̸� ���� �� ���� ��󿡼� 
		// �ð� �ݴ� �����̸� �ﰢ���� ������ ���ϴ� ������ 
		// ���ֵǰ� �ð� �����̸� �ĸ��� ���ϴ� ������ ���ֵ˴ϴ�. 
		// �� �Ű������� FALSE �̸� �� �ݴ��Դϴ�.
		//INT DepthBias;
		// ������ �ȼ��� �߰��� ���� ���Դϴ�. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//FLOAT DepthBiasClamp;
		// �ȼ��� �ִ� ���� ����. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//FLOAT SlopeScaledDepthBias;
		// �־��� �ȼ��� ���⿡ ���� ��Į��. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//BOOL DepthClipEnable;
		// �Ÿ��� ���� Ŭ������ Ȱ��ȭ�մϴ�.
		// �ϵ����� �׻� ������ȭ�� ��ǥ�� x �� y Ŭ������ �����մϴ�.
		// DepthClipEnable�� �⺻���� TRUE �� ���� �Ǹ� �ϵ��� z 
		// ���� �ڸ��ϴ�(��, �ϵ����� ���� �˰����� ������ �ܰ踦 �����մϴ�).
		//BOOL ScissorEnable;
		// ���� �簢�� �ø��� Ȱ��ȭ�մϴ�. Ȱ�� ���� �簢�� �ܺ��� ��� �ȼ��� �߷����ϴ�.
		//BOOL MultisampleEnable;
		// ���� ���� ��Ƽ�ٸ����(MSAA) ���� ��󿡼� �纯�� �Ǵ� ���� ���� ��Ƽ�ٸ���� 
		// �˰����� ������� ���θ� �����մϴ�. �纯�� ���� ��Ƽ �ٸ���� �˰����� 
		// ����Ϸ��� TRUE �� ���� �ϰ� ���� ���� ��Ƽ �ٸ���� �˰����� ����Ϸ��� 
		// FALSE �� �����մϴ�. �� ����� ���� �ڼ��� ������ ��� �����ϼ���.
		//BOOL AntialiasedLineEnable;
		// �� ��Ƽ�ٸ������ Ȱ��ȭ���� ���θ� �����մϴ�. �� �׸��⸦ �����ϰ� MultisampleEnable�� 
		// FALSE �� ��쿡�� ����˴ϴ� . �� ����� ���� �ڼ��� ������ ��� �����ϼ���.

		// ���̾� �������� ������ ǥ��
		// Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Desc);

		// ������
		std::shared_ptr<GameEngineRasterizer> Res1 = GameEngineRasterizer::Create("2DTranslucent", Desc);
		// ������ 
		std::shared_ptr<GameEngineRasterizer> Res2 = GameEngineRasterizer::Create("2DBlink", Desc);
	}
	{
		{
			// ���������� ����
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			// ���������������ο��� ����� ���ҽ� ����
			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("EngineDepth");
		}

		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Merge");
			Pipe->SetVertexBuffer("FullRect");
			Pipe->SetIndexBuffer("FullRect");
			Pipe->SetVertexShader("MergeShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("MergeShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("AlwayDepth");

			GameEngineRenderTarget::RenderTargetUnitInit();
		}

		// �׽�Ʈ 
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTranslucentTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TranslucentShader.hlsl");
			Pipe->SetRasterizer("2DTranslucent");
			Pipe->SetPixelShader("TranslucentShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("EngineDepth");
		}

		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DBlinkTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("BlinkShader.hlsl");
			Pipe->SetRasterizer("2DBlink");
			Pipe->SetPixelShader("BlinkShader.hlsl");
			Pipe->SetBlendState("AlphaBlend");
			Pipe->SetDepthState("EngineDepth");
		}
	}
}

// 
void GameEngineCore::CoreResourcesEnd()
{
	// ������ ���ҽ����� ��� �������ش�. 
	// shard ptr ������� ���� ���۷���ī��Ʈ�� 0 �̵Ǹ� �ڵ����� ���ŵ�����
	// ���ϴ½����� �����Ǵ� ���� Ȯ���� �ϰ�, ���⼭ ���ŵ��� �ʴ´ٸ� ������ �ִ� ���̶�� �Ǵ��ϱ� ���ؼ�. 
	GameEngineMesh::ResourcesClear();
	GameEngineBlend::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineDepthState::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
	GameEngineConstantBuffer::ResourcesClear();
	GameEngineRenderingPipeLine::ResourcesClear();
}
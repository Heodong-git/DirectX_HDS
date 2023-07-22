#include "PrecompileHeader.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineVertexBuffer.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#include "TitleLevel.h"
#include "ClubLevel_00.h"
#include "ClubLevel_01.h"
#include "ClubLevel_02.h"
#include "ClubLevel_03.h"
#include "ClubLevel_04.h"

#include "ClubLevel_Boss.h"
#include "ClubLevel_Boss_01.h"

#include "TitleEditer.h"
#include "StageEditer.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::ContentsResourcesCreate()
{
	{
		// ���̴� �ε� 
		GameEngineDirectory NewDir;
		// ���ڷ� �Է��� ������ �����ϴ� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("MyShader");

		// �ӽú���
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}
	}
	
	{
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// �ؽ�ó�� �ָ������� ��������
		// �ȹ�����.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAP", SamperData);
	}

	{
		// ���������μ���
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("My2DTexture");

		//Pipe->SetVertexBuffer("Rect");
		//Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("MyShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("MyShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Fade");

		//Pipe->SetVertexBuffer("FullRect");
		//Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("OldTV");

		Pipe->SetVertexShader("OldTVShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("OldTVShader.hlsl");
		Pipe->SetBlendState("OldFilm");
		Pipe->SetDepthState("EngineDepth");
	}
	// �õ��ʸ� ���������� ����
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("OldFilm");

		Pipe->SetVertexShader("OldFilmShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("OldFilmShader.hlsl");
		Pipe->SetBlendState("OldFilm");
		Pipe->SetDepthState("EngineDepth");
	}



	// �۸�ġ ���������� ����
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Glitch");

		Pipe->SetVertexShader("GlitchShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("GlitchShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("DebugRect");
		//Pipe->SetVertexBuffer("Rect");
		//Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("DebugMeshRender.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("DebugMeshRender.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameStart()
{
	// gui
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<TitleEditer>("Title_Editer");
		Window->Off();
	}
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<StageEditer>("Debug_State");
		Window->Off();
	}

	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<ClubLevel_00>("ClubLevel_00");
	GameEngineCore::CreateLevel<ClubLevel_01>("ClubLevel_01");
	GameEngineCore::CreateLevel<ClubLevel_02>("ClubLevel_02");
	GameEngineCore::CreateLevel<ClubLevel_03>("ClubLevel_03");
	//GameEngineCore::CreateLevel<ClubLevel_04>("ClubLevel_04");				 // ���� ����
	GameEngineCore::CreateLevel<ClubLevel_Boss>("ClubLevel_Boss");
	GameEngineCore::CreateLevel<ClubLevel_Boss_01>("ClubLevel_Boss_01");

	GameEngineCore::ChangeLevel("TitleLevel");
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{
}
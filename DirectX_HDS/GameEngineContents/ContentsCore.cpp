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
		// 쉐이더 로드 
		GameEngineDirectory NewDir;
		// 인자로 입력한 폴더가 존재하는 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("MyShader");

		// 임시변경
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineShader::AutoCompile(Files[i]);
		}
	}
	
	{
		// 파이프라인세팅
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

// 게임이 실행되면 동작해야할 함수를 호출
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
	GameEngineCore::CreateLevel<ClubLevel_04>("ClubLevel_04");
	GameEngineCore::CreateLevel<ClubLevel_Boss>("ClubLevel_Boss");
	GameEngineCore::CreateLevel<ClubLevel_Boss_01>("ClubLevel_Boss_01");

	GameEngineCore::ChangeLevel("TitleLevel");
}

// 게임이 종료되면 동작해야할 함수를 호출
void ContentsCore::GameEnd()
{
}
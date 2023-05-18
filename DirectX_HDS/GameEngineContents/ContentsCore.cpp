#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "CTutorialLevel.h"
#include "ClubLevel_00.h"
#include "ClubLevel_01.h"
#include "ClubLevel_02.h"

#include "ClubBossLevel.h"
#include "TitleEditer.h"
#include "StageEditer.h"

// 얘는 스태틱으로 가자 
#include "PlayManager.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::ContentsResourcesCreate()
{
	// 텍스쳐 로드만 각각 필요한 레벨에서. 레벨체인지하게 될 경우 로드한 리소스 삭제까지. 
}

// 게임이 실행되면 동작해야할 함수를 호출
void ContentsCore::GameStart()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<ClubLevel_00>("ClubLevel_00");
	GameEngineCore::CreateLevel<ClubLevel_01>("ClubLevel_01");
	GameEngineCore::CreateLevel<ClubLevel_02>("ClubLevel_02");
	GameEngineCore::CreateLevel<ClubBossLevel>("ClubBossLevel");

	GameEngineCore::ChangeLevel("ClubLevel_00");

	// gui
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<TitleEditer>("Title_Editer");
		Window->Off();
	}
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<StageEditer>("Debug_State");
		Window->Off();
	}
}

// 게임이 종료되면 동작해야할 함수를 호출
void ContentsCore::GameEnd()
{
}
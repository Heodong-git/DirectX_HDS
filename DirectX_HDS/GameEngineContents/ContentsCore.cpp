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

// ��� ����ƽ���� ���� 
#include "PlayManager.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::ContentsResourcesCreate()
{
	// �ؽ��� �ε常 ���� �ʿ��� ��������. ����ü�����ϰ� �� ��� �ε��� ���ҽ� ��������. 
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
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

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{
}
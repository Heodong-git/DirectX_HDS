#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "CTutorialLevel.h"
#include "ClubLevel.h"
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
	GameEngineCore::CreateLevel<ClubLevel>("ClubLevel");
	GameEngineCore::CreateLevel<ClubBossLevel>("ClubBossLevel");

	GameEngineCore::ChangeLevel("ClubLevel");

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
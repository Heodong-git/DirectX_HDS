#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineGUI.h>
#include "PlayLevel.h"
#include "CTestLevel.h"
#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include "CTutorialLevel.h"
#include "ClubLevel.h"
#include "ClubBossLevel.h"
#include "TitleEditer.h"
#include "StageEditer.h"
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
	ContentsResourcesCreate();

	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");

	// �������� �� ����ü���� , ������ �̸��� �־����� �ʴ´ٸ�
	// Ŭ���� �̸��� ������ �̸����� ���� ����
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	// GameEngineCore::CreateLevel<CTutorialLevel>("TutorialLevel");
	GameEngineCore::CreateLevel<ClubLevel>("ClubLevel");
	GameEngineCore::CreateLevel<ClubBossLevel>("Stage02Level");

	//GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");

	// gui
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<TitleEditer>("Title_Editer");
		Window->Off();
	}
	{
		std::shared_ptr<GameEngineGUIWindow> Window = GameEngineGUI::GUIWindowCreate<StageEditer>("Stage_Editer");
		Window->Off();
	}
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{
	// 
	PlayManager::DestroyInst();
}
#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineGUI.h>
#include "PlayLevel.h"
#include "CTestLevel.h"
#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include "CTutorialLevel.h"
#include "CStageLevel_01.h"
#include "CStageLevel_02.h"
#include "CGameEditer.h"

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
	GameEngineCore::CreateLevel<CTitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<CTutorialLevel>("TutorialLevel");
	GameEngineCore::CreateLevel<CStageLevel_01>("StageLevel_01");
	GameEngineCore::CreateLevel<CStageLevel_02>("StageLevel_02");

	//GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");


	// gui
	GameEngineGUI::GUIWindowCreate<CGameEditer>("Title_Editer");
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{

}
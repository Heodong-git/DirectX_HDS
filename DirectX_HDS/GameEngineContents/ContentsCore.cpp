#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "CTestLevel.h"
#include "CTitleLevel.h"
#include "CStageLevel_01.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameStart()
{
	GameEngineCore::CreateLevel<CTitleLevel>();
	GameEngineCore::CreateLevel<CStageLevel_01>();
	GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("CTestLevel");
}

// ������ ����Ǹ� �����ؾ��� �Լ��� ȣ��
void ContentsCore::GameEnd()
{

}
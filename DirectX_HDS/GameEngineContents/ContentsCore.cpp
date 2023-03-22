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

// 게임이 실행되면 동작해야할 함수를 호출
void ContentsCore::GameStart()
{
	GameEngineCore::CreateLevel<CTitleLevel>();
	GameEngineCore::CreateLevel<CStageLevel_01>();
	GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("CTestLevel");
}

// 게임이 종료되면 동작해야할 함수를 호출
void ContentsCore::GameEnd()
{

}
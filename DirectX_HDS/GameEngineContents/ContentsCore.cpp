#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 게임이 실행되면 동작해야할 함수를 호출
void ContentsCore::GameStart()
{
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

// 게임이 종료되면 동작해야할 함수를 호출
void ContentsCore::GameEnd()
{

}
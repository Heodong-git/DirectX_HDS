#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "CTestLevel.h"
#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include "CStageLevel_01.h"
#include "CStageLevel_02.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 게임이 실행되면 동작해야할 함수를 호출
void ContentsCore::GameStart()
{
	// 레벨생성 후 레벨체인지 , 생성시 이름을 넣어주지 않는다면
	// 클래스 이름과 동일한 이름으로 레벨 생성
	GameEngineCore::CreateLevel<CTitleLevel>();
	GameEngineCore::CreateLevel<CStageLevel_01>();
	GameEngineCore::CreateLevel<CStageLevel_02>();

	GameEngineCore::CreateLevel<CTestLevel>();
	GameEngineCore::ChangeLevel("CTestLevel");
}

// 게임이 종료되면 동작해야할 함수를 호출
void ContentsCore::GameEnd()
{

}
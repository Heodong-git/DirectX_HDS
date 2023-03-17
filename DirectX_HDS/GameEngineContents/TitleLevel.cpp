#include "TitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Loading()
{
	// 생성될 때 얘가 동작, 타이틀레벨이 생성되면 만들어야 할 녀석들을 여기서 만든다. 
	// TimeEvent.AddEvent(5.0f, std::bind(&TitleLevel::TestMsg, this), true);

	// 람다 문법
	// 이름이 없는 함수를 만들어내는 문법.
	std::function<void()> Test = []
	{
		MsgTextBox("이벤트 정상 작동");
	};

	TimeEvent.AddEvent(1.0f, Test, true);
}


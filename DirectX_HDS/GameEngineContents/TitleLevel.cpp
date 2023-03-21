#include "TitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

// 부모함수를 재정의 했기 때문에 이녀석이 호출됨
void TitleLevel::Loading()
{
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test0 =
		[](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("도주");
	};

	// 람다 문법
	// 이름이 없는 함수를 만들어내는 문법.
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test = 
		[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("공격");

		_Manager->AddEvent(3.0f, Test0, false);
	};

	 TimeEvent.AddEvent(3.0f, Test, false);
}


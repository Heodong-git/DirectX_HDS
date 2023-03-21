#include "CTitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

// TEST
#include <GameEngineBase/GameEngineTimeEvent.h>

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

void TestFunction(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	int a = 0;
}

// 부모함수를 재정의 했기 때문에 이녀석이 호출됨
void CTitleLevel::Loading()
{
	// 람다 : 이름이 없는 함수를 만들어주는 기능
	// 두개의 인자를 받는 function 객체에
	// [](인자)
	// {
	// }
	// 의 형태로 이름없는 함수를 만들어 대입할 수 있다. 코드블록 내부에 동작할 코드 작성
	// 이런 형태로 이름 없는 함수를 만들어주고 내부에서 무언가를 하게 만든다. 
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test = 
		[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("공격");

		_Manager->AddEvent(3.0f, TestFunction, false);
	};

	// 소유한 타임이벤트의 함수호출
	// 람다 테스트용으로 만든 Test 함수를 호출 한것. 
	TimeEvent.AddEvent(5.0f, Test, false);
}


#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{
}

GameEngineTimeEvent::~GameEngineTimeEvent()
{
}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void()> _Event, bool _Loop /*= false*/)
{
	// 기본생성자가 있다면 내부에서 그 기본생성자를 가지고 만들어준다. ?? 
	// 구글검색요망ㅋㅋ TimeEvent 라는 녀석을 기본생성자를 가지고 만들어서 넣어주고 걔를 반환하는건가 ?
	TimeEvent& NewEvent = Event.emplace_back();
	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	for (size_t i = 0; i < Event.size(); i++)
	{
		Event[i].CurTime -= _DeltaTime;

		if (Event[i].CurTime < 0.0f)
		{
			Event[i].Event();
			if (true == Event[i].Loop)
			{
				Event[i].CurTime = Event[i].Time;
			}
		}
	}
}
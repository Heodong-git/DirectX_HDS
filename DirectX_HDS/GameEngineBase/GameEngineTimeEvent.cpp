#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{
}

GameEngineTimeEvent::~GameEngineTimeEvent()
{
}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop /*= false*/)
{
	// 기본 생성자가 있으면
	// 그냥 자기가 내부에서 기본생성자를 사용하여 만들어주는 기능
	TimeEvent& NewEvent = Events.emplace_back();
	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	std::list<TimeEvent>::iterator StartIter = Events.begin();
	std::list<TimeEvent>::iterator EndIter = Events.end();

	for (; StartIter != EndIter;)
	{
		// 현재이벤트 = *iter
		TimeEvent& CurEvent = *StartIter;

		// 이벤트의 시간값 누적감소
		CurEvent.CurTime -= _DeltaTime;

		// 시간값이 0보다 작아지게 된다면 동작
		if (CurEvent.CurTime < 0.0f)
		{
			CurEvent.Event(CurEvent, this);
			CurEvent.CurTime = CurEvent.Time;

			// Loop 가 false 라면 동작했기 때문에 이벤트를 제거한다. 
			if (false == CurEvent.Loop)
			{
				StartIter = Events.erase(StartIter);
				continue;
			}
		}

		++StartIter;
	}
}
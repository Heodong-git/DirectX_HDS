#pragma once
#include <functional>
#include <vector>

class GameEngineTimeEvent
{
public:

	class TimeEvent
	{
		friend GameEngineTimeEvent;

		bool IsLive = true;
		float CurTime = 0.0f;
		std::function<void(TimeEvent&, GameEngineTimeEvent*)> Event;
		bool Loop = false;

	public:
		float Time = 0.0f;
	};

public:
	GameEngineTimeEvent();
	~GameEngineTimeEvent();

	GameEngineTimeEvent(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent(GameEngineTimeEvent&& _Other) noexcept = delete;
	GameEngineTimeEvent& operator=(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent& operator=(GameEngineTimeEvent&& _Other) noexcept = delete;

	void AddEvent(float Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop = false);
	void Update(float _DeltaTime);

private:
	
	std::list<TimeEvent> Events;
};

// GameEngineTimeEvent 를 사용하려는 클래스가 가지게 하고 
// 원하는 시점에 AddEvent 함수를 호출하여 이벤트를 추가하여 사용 
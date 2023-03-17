#pragma once
#include <functional>
#include <vector>

// 시간과 관련된 이벤트를 수행할 때 사용하는 클래스
class GameEngineTimeEvent
{
private:
	class TimeEvent
	{
		friend GameEngineTimeEvent;

		bool IsLive = true;
		float CurTime = 0.0f;
		float Time = 0.0f;
		std::function<void()> Event;
		bool Loop = false;
	};

public:
	// constrcuter destructer
	GameEngineTimeEvent();
	~GameEngineTimeEvent();

	// delete Function
	GameEngineTimeEvent(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent(GameEngineTimeEvent&& _Other) noexcept = delete;
	GameEngineTimeEvent& operator=(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent& operator=(GameEngineTimeEvent&& _Other) noexcept = delete;

	// 이벤트 추가
	// 반복될 시간, 실행할 함수, 반복여부
	void AddEvent(float Time, std::function<void()> _Event, bool _Loop = false);

	void Update(float _DeltaTime);

private:
	// 배열에 TimeEvent 저장
	std::vector<TimeEvent> Event;
};


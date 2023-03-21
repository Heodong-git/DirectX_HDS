#pragma once
#include <functional>
#include <vector>

class GameEngineTimeEvent
{
public:
	// Ÿ���̺�Ʈ�� ������� 
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
	// constrcuter destructer
	GameEngineTimeEvent();
	~GameEngineTimeEvent();

	// delete Function
	GameEngineTimeEvent(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent(GameEngineTimeEvent&& _Other) noexcept = delete;
	GameEngineTimeEvent& operator=(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent& operator=(GameEngineTimeEvent&& _Other) noexcept = delete;

	// �̺�Ʈ �߰�
	// �ݺ��� �ð�, ������ �Լ�, �ݺ�����
	void AddEvent(float Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop = false);

	void Update(float _DeltaTime);

private:
	// �迭�� TimeEvent ����
	std::list<TimeEvent> Events;
};


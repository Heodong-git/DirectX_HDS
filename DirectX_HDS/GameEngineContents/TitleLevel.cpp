#include "TitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

// �θ��Լ��� ������ �߱� ������ �̳༮�� ȣ���
void TitleLevel::Loading()
{
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test0 =
		[](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("����");
	};

	// ���� ����
	// �̸��� ���� �Լ��� ������ ����.
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test = 
		[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("����");

		_Manager->AddEvent(3.0f, Test0, false);
	};

	 TimeEvent.AddEvent(3.0f, Test, false);
}


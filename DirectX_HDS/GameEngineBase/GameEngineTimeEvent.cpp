#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{
}

GameEngineTimeEvent::~GameEngineTimeEvent()
{
}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop /*= false*/)
{
	// �⺻ �����ڰ� ������
	// �׳� �ڱⰡ ���ο��� �⺻�����ڸ� ����Ͽ� ������ִ� ���
	TimeEvent& NewEvent = Events.emplace_back();
	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	// ����Ʈ ��ȸ
	std::list<TimeEvent>::iterator StartIter = Events.begin();
	std::list<TimeEvent>::iterator EndIter = Events.end();

	for (; StartIter != EndIter;)
	{
		// �����̺�Ʈ = *iter
		TimeEvent& CurEvent = *StartIter;

		// �̺�Ʈ�� �ð��� ��������
		CurEvent.CurTime -= _DeltaTime;

		// �ð����� 0���� �۾����� �ȴٸ� ����
		if (CurEvent.CurTime < 0.0f)
		{
			// ���� �̺�Ʈ�� ���� �̺�Ʈ�Լ� ȣ��
			CurEvent.Event(CurEvent, this);
			// �̺�Ʈ�� ����Ǿ��� ������ �ð��ʱ�ȭ(���ʽð����� ����)
			CurEvent.CurTime = CurEvent.Time;

			// ���Ŀ�
			// Loop �� false ��� �����߱� ������ �̺�Ʈ�� �����Ѵ�. 
			if (false == CurEvent.Loop)
			{
				// iterator �� erase �Լ��� ȣ���߱� ������ 
				// StartIter ���� ������ ����� ������尡 ��ȯ�Ǿ����� ��Ƽ��
				StartIter = Events.erase(StartIter);
				continue;
			}
		}

		++StartIter;
	}
}
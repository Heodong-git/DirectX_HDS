#include "PrecompileHeader.h"
#include "CKatanaZero_Level.h"
#include "CMouse.h"


CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void RecordActor(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	// �ߵ����� ���⼭ ȣ��ɶ����� ���͵��� ������ �����ϸ� �ȴ�. 
}

void CKatanaZero_Level::Start()
{
	if (true == GetRecordUse())
	{
		// ������ Play Level �� ������ ���������� ���ص� �ð� �������� �����Ѵ�. 
		// Replay ��� ���� Ȱ���Ұ��̰�, ���÷��̰� �ʿ���� ������ ������� �����ž�
		TimeEvent.AddEvent(m_SaveInterval, RecordActor, true);
	}
}



void CKatanaZero_Level::Update(float _DeltaTime)
{
	// GameEngineLevel �� update �� virtual �� �������شٸ� ����
	GameEngineLevel::Update(_DeltaTime);

	std::shared_ptr<CMouse> Mouse = GetMouse();
	if (nullptr != Mouse)
	{
		m_CurMouseLocalPos = Mouse->GetTransform()->GetLocalPosition();
	}

	if (m_MaxTimeLimit <= GetTimeLimit())
	{
		if (false == IsTimeOver())
		{
			// false �϶��� ������ �κе��� �������ְ� true�� �����ؼ�
			// ������ ������ �ʰ� ����
			TimeOver();
		}
		return;
	}
	// ���ѽð����� 
	TimeIncrease(_DeltaTime);
	// TimeEvent.AddEvent(3.0f, )
}

// ����� �������� �ҷ����� �����
void CKatanaZero_Level::ReversePlay(float _DeltaTime)
{
}

void CKatanaZero_Level::TimeOver()
{
	if (false == IsTimeOver())
	{
		m_TimeOver = true;
		// �÷��̾���
		// �����ð��� ����� ȭ�� ��� 
	}
	
}

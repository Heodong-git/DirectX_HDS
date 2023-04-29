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
	// 잘들어오고 여기서 호출될때마다 액터들의 정보를 저장하면 된다. 
}

void CKatanaZero_Level::Start()
{
	if (true == GetRecordUse())
	{
		// 각각의 Play Level 은 레벨의 액터정보를 정해둔 시간 간격으로 저장한다. 
		// Replay 기능 사용시 활용할것이고, 리플레이가 필요없는 레벨은 사용하지 않을거야
		TimeEvent.AddEvent(m_SaveInterval, RecordActor, true);
	}
}



void CKatanaZero_Level::Update(float _DeltaTime)
{
	// GameEngineLevel 의 update 를 virtual 로 변경해준다면 삭제
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
			// false 일때만 수행할 부분들을 수행해주고 true로 변경해서
			// 여러번 들어오지 않게 설정
			TimeOver();
		}
		return;
	}
	// 제한시간증가 
	TimeIncrease(_DeltaTime);
	// TimeEvent.AddEvent(3.0f, )
}

// 저장된 정보들을 불러오고 역재생
void CKatanaZero_Level::ReversePlay(float _DeltaTime)
{
}

void CKatanaZero_Level::TimeOver()
{
	if (false == IsTimeOver())
	{
		m_TimeOver = true;
		// 플레이어사망
		// 일정시간뒤 역재생 화면 출력 
	}
	
}

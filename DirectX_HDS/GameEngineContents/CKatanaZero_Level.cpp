#include "PrecompileHeader.h"
#include "CKatanaZero_Level.h"
#include "CCursor.h"
#include <GameEngineCore/GameEngineCamera.h>


CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Start()
{
	CameraLoad();
	if (true == GetRecordUse())
	{
	}
}

void CKatanaZero_Level::Update(float _DeltaTime)
{
	// GameEngineLevel �� update �� virtual �� �������شٸ� ����
	GameEngineLevel::Update(_DeltaTime);

	// ���� Ŀ���� nullptr �� �ƴ϶�� 
	// �޾ƿͼ� ������������ ����
	std::shared_ptr<CCursor> Cursor = GetCursor();
	if (nullptr != Cursor)
	{
		m_CurMouseLocalPos = Cursor->GetTransform()->GetLocalPosition();
	}

	//if (m_MaxTimeLimit <= GetTimeLimit())
	//{
	//	if (false == IsTimeOver())
	//	{
	//		// false �϶��� ������ �κе��� �������ְ� true�� �����ؼ�
	//		// ������ ������ �ʰ� ����
	//		TimeOver();
	//	}
	//	return;
	//}

	//// ���ѽð����� 
	//TimeIncrease(_DeltaTime);
	//// TimeEvent.AddEvent(3.0f, )
}

void CKatanaZero_Level::LevelChangeStart()
{
	
}

void CKatanaZero_Level::CameraLoad()
{
	// ī�޶���
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });
}

#include "PrecompileHeader.h"
#include "CKatanaZero_Level.h"
#include <GameEngineBase/GameEngineDebug.h>


CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Update(float _DeltaTime)
{
	if (115.0f >= GetTimeLimit())
	{
		//MsgAssert("�����");
	}

	// ���ѽð����� 
	TimeDecrease(_DeltaTime);

	// GameEngineLevel �� update �� virtual �� �������شٸ� ����
	GameEngineLevel::Update(_DeltaTime);
}

bool CKatanaZero_Level::RecordTimeCheck()
{
	return true;
}

// ���� �ð����� ���� ������ ���� ���� ����Ͽ� ����
void CKatanaZero_Level::RecordActor()
{
}

// ����� �������� �ҷ����� �����
void CKatanaZero_Level::ReversePlay(float _DeltaTime)
{
}

void CKatanaZero_Level::TimeOver()
{
	// �÷��̾� ���, �ڸ���� 
}
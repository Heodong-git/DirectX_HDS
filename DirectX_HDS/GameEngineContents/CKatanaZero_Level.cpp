#include "CKatanaZero_Level.h"

CKatanaZero_Level::CKatanaZero_Level()
{
}

CKatanaZero_Level::~CKatanaZero_Level()
{
}

void CKatanaZero_Level::Start()
{
	
}

void CKatanaZero_Level::Update(float _DeltaTime)
{
	if (110.0f >= GetTimeLimit())
	{
		int a = 0;
	}

	// ���ѽð����� 
	TimeDecrease(_DeltaTime);

	GameEngineLevel::Update(_DeltaTime);
}

void CKatanaZero_Level::TimeOver()
{
	// �÷��̾� ���, �ڸ���� 
}
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ������ �����ð����� �������������ϴ� ����� �ʿ���
class CKatanaZero_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	CKatanaZero_Level();
	~CKatanaZero_Level();

	// delete Function
	CKatanaZero_Level(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level(CKatanaZero_Level&& _Other) noexcept = delete;
	CKatanaZero_Level& operator=(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level& operator=(CKatanaZero_Level&& _Other) noexcept = delete;

	// ���ѽð� 
	inline void SetTimeLimit(float _Time)
	{
		m_TimeLimit = _Time;
	}

	// ���ѽð� ��ȯ
	inline float GetTimeLimit()
	{
		return m_TimeLimit;
	}

	// ���ѽð� ���� 
	inline void TimeDecrease(float _DeltaTime)
	{
		m_TimeLimit -= _DeltaTime;
	}

	// Ÿ�ӿ���
	void TimeOver();
protected:
	void Update(float _DeltaTime);

private:
	// �ӽ�, ���������� ���ѽð�
	float m_TimeLimit = 120.0f;
};
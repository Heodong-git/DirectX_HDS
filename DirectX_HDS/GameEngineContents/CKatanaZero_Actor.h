#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class CKatanaZero_Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	CKatanaZero_Actor();
	~CKatanaZero_Actor();

	// delete Function
	CKatanaZero_Actor(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor(CKatanaZero_Actor&& _Other) noexcept = delete;
	CKatanaZero_Actor& operator=(const CKatanaZero_Actor& _Other) = delete;
	CKatanaZero_Actor& operator=(CKatanaZero_Actor&& _Other) noexcept = delete;


protected:
	// ���� �̷��� ���� �׳� ��������� ������ �ᵵ ������ �������� �̰� �� ���� �� ����.
	inline void SetAngle(float _Angle)
	{
		m_Angle = _Angle;
	}

	inline float GetAngle() const
	{
		return m_Angle;
	}

private:
	float m_Angle = 0.0f;
};

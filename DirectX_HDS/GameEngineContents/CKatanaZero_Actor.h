#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	inline void SetAngle(float _Angle)
	{
		m_Angle = _Angle;
	}

	inline float GetAngle() const
	{
		return m_Angle;
	}

	// �ڽ��� ������ ���̺�,�ε��ϴ� ���.. �ε� 
	// ���� ������ �ִ� ������ �ٸ���... �� 
	// ���ͷ��ڵ����� Ŭ������ ���� ������ �ְ� �ϰ� �� Ŭ���� ������ ������ ���?

protected:

private:
	float m_Angle = 0.0f;


	// -------------------------recording info-------------------------------
	// ������� �ʿ��� ��ȭ�� �������� �Ʒ� �κп� �ۼ��ϰ�, �Լ��� �� �������� �����ϰ�, �ε��ϴ� �Լ��� ����? 
};

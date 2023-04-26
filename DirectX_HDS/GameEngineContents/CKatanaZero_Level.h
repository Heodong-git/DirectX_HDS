#pragma once
#include <GameEngineCore/GameEngineLevel.h>

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
	inline void TimeIncrease(float _DeltaTime)
	{
		m_TimeLimit += _DeltaTime;
	}

	// Level�� ���鶧 ��ȭ�� �ʿ���� ������ �̰� ȣ���ؼ� false�� �����. 
	inline void RecodingOff()
	{
		m_Recording = false;
	}

	inline bool GetRecordUse()
	{
		return m_Recording;
	}

	inline bool IsTimeOver() const
	{
		return m_TimeOver;
	}

	std::shared_ptr<class CBoss_HeadHunter> GetBoss()
	{
		return m_Boss;
	}

	std::shared_ptr<class CPlayer> GetPlayer()
	{
		return m_Player;
	}

	void SetPlayer(std::shared_ptr<class CPlayer> _Player)
	{
		m_Player = _Player;
	}

	void SetBoss(std::shared_ptr<class CBoss_HeadHunter> _Boss)
	{
		m_Boss = _Boss;
	}

	void SetMouse(std::shared_ptr<class CMouse> _Mouse)
	{
		m_Mouse = _Mouse;
	}

	std::shared_ptr<class CMouse> GetMouse()
	{
		return m_Mouse;
	}

protected:
	// ��ȭ�ϰ� ����� �ؾ��ϴ� ���������� �������� Start���� �긦 ȣ���ϸ� �ǰ� �Ϸ��� �ߴµ�
	// �׳� ��ȣ���ϰų� �������̵����� ó���ϰ�, recording == true �� ���������� ��ȭ 
	void Start() override;
	void Update(float _DeltaTime);


private:
	std::shared_ptr<class CPlayer> m_Player = nullptr;
	std::shared_ptr<class CBoss_HeadHunter> m_Boss = nullptr;
	std::shared_ptr<class CMouse> m_Mouse = nullptr;

	bool m_Wait = true;
	bool m_Playing = false; 

	// Ÿ�ӿ���
	void TimeOver();

	// �����
	void ReversePlay(float _DeltaTime);

	bool m_Recording = true;
	bool m_TimeOver = false;

	// �ӽ�, ���������� ���ѽð�
	float m_TimeLimit = 0.0f;
	float m_MaxTimeLimit = 4.0f;
	float m_SaveInterval = 2.0f;
};
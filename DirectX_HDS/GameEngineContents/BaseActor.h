#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>

// BaseState ???? 

class BaseActor : public GameEngineActor
{
	// �������� �ʱ���·� �����ϰ� �� ���
	// ���͵��� �ʱ���·� �����ϱ� ���� 
	friend class BaseLevel;
public:
	// constrcuter destructer
	BaseActor();
	~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	class BaseLevel* GetReturnCastLevel() const;

	inline void SetInitPos(float4& _Pos)
	{
		m_InitPos = _Pos;
	}

	inline const float4 GetInitPos() const
	{
		return m_InitPos;
	}

	virtual void BulletCollision() {};
	
	void SetDeath()
	{
		m_IsDeath = true;
	}

	// ���̽����Ϳ� ����üũ, ���͵��� ��Ʈ�׶��� state ���� ���� true�� �������ش�. 
	bool DeathCheck()
	{
		return m_IsDeath;
	}

protected:
	void Update(float _DeltaTime) override;

	// ����� ����ġ
	virtual void DebugSwitch()
	{
		if (true == IsDebug())
		{
			DebugOff();
		}

		else if (false == IsDebug())
		{
			DebugOn();
		}
	}

	bool m_IsDeath = false;
	
private:

	// BaseActor���� ���� �긦 �������̵� 
	virtual void Reset() {};
	float4 m_InitPos = {};
};

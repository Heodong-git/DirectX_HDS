#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:
	// BaseActor���� ���� �긦 �������̵� 
	virtual void Reset() {};
	float4 m_InitPos = {};
};

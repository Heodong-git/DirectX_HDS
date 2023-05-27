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

	// �ʿ��Ѱ�..? ���� �ʿ��� 
	class BaseLevel* GetReturnCastLevel() const;

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

	
	// -------------------------recording info-------------------------------
	// ������� �ʿ��� ��ȭ�� �������� �Ʒ� �κп� �ۼ��ϰ�, �Լ��� �� �������� �����ϰ�, �ε��ϴ� �Լ��� ����? 
};

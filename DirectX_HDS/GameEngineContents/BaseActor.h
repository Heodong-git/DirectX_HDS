#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BaseActor : public GameEngineActor
{
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

protected:
	void Update(float _DeltaTime) override;

private:
	// -------------------------recording info-------------------------------
	// ������� �ʿ��� ��ȭ�� �������� �Ʒ� �κп� �ۼ��ϰ�, �Լ��� �� �������� �����ϰ�, �ε��ϴ� �Լ��� ����? 
};
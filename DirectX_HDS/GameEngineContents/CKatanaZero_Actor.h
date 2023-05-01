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

protected:
	void Update(float _DeltaTime) override;

private:
	// -------------------------recording info-------------------------------
	// ������� �ʿ��� ��ȭ�� �������� �Ʒ� �κп� �ۼ��ϰ�, �Լ��� �� �������� �����ϰ�, �ε��ϴ� �Լ��� ����? 
};

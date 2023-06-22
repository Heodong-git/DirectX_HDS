#pragma once
#include "BaseActor.h"

enum class SlidingDoorState
{
	NONE,
	CLOSE,
	OPEN,
};

// ���� :
class SlidingDoor : public BaseActor
{
public:
	// constrcuter destructer
	SlidingDoor();
	~SlidingDoor();

	// delete Function
	SlidingDoor(const SlidingDoor& _Other) = delete;
	SlidingDoor(SlidingDoor&& _Other) noexcept = delete;
	SlidingDoor& operator=(const SlidingDoor& _Other) = delete;
	SlidingDoor& operator=(SlidingDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� ���ҽ� �ε�׻���
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_BaseRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DoorRender = nullptr;

	// ��¾���� Ȯ���� ���� 
	// �־�߰ڱ��� 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
private:

	// ���� 
	virtual void Reset() override;
	// ���°� ����
	void ChangeState(SlidingDoorState _State);
	// ���� ���°��� ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	SlidingDoorState m_CurState = SlidingDoorState::CLOSE;
	SlidingDoorState m_PrevState = SlidingDoorState::NONE;
	SlidingDoorState m_NextState = SlidingDoorState::NONE;

	void CloseStart();
	void CloseUpdate(float _DeltaTime);
	void CloseEnd();

	void OpenStart();
	void OpenUpdate(float _DeltaTime);
	void OpenEnd();
};

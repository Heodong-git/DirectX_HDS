#pragma once
#include "BaseActor.h"

enum class ClubDoorState
{
	NONE,
	CLOSE,
	OPEN,
};

// ���� :
class ClubDoor : public BaseActor
{
public:
	// constrcuter destructer
	ClubDoor();
	~ClubDoor();

	// delete Function
	ClubDoor(const ClubDoor& _Other) = delete;
	ClubDoor(ClubDoor&& _Other) noexcept = delete;
	ClubDoor& operator=(const ClubDoor& _Other) = delete;
	ClubDoor& operator=(ClubDoor&& _Other) noexcept = delete;

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

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

private:
	// ���� 
	virtual void Reset() override;
	// ���°� ����
	void ChangeState(ClubDoorState _State);
	// ���� ���°��� ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	ClubDoorState m_CurState = ClubDoorState::CLOSE;
	ClubDoorState m_PrevState = ClubDoorState::NONE;
	ClubDoorState m_NextState = ClubDoorState::NONE;

	void CloseStart();
	void CloseUpdate(float _DeltaTime);
	void CloseEnd();

	void OpenStart();
	void OpenUpdate(float _DeltaTime);
	void OpenEnd();
};

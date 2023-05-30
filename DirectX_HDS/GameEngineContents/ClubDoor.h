#pragma once
#include "BaseActor.h"

enum class ClubDoorState
{
	NONE,
	CLOSE,
	OPEN,
};

// 설명 :
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

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 리소스 로드및생성
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

private:
	// 리셋 
	virtual void Reset() override;
	// 상태값 변경
	void ChangeState(ClubDoorState _State);
	// 현재 상태값에 따른 업데이트 
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

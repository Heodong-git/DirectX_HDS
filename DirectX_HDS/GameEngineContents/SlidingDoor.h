#pragma once
#include "BaseActor.h"

enum class SlidingDoorState
{
	NONE,
	CLOSE,
	OPEN,
};

// 설명 :
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

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 리소스 로드및생성
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_BaseRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DoorRender = nullptr;

	// 얘는없어도될 확률이 높음 
	// 있어야겠구나 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
private:

	// 리셋 
	virtual void Reset() override;
	// 상태값 변경
	void ChangeState(SlidingDoorState _State);
	// 현재 상태값에 따른 업데이트 
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

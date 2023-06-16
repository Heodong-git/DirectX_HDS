#pragma once
#include "BaseActor.h"

enum class IronDoorState
{
	NONE,
	CLOSE,
	OPEN,
};

// 설명 :
class IronDoor : public BaseActor
{
	friend class Player;
public:
	// constrcuter destructer
	IronDoor();
	~IronDoor();

	// delete Function
	IronDoor(const IronDoor& _Other) = delete;
	IronDoor(IronDoor&& _Other) noexcept = delete;
	IronDoor& operator=(const IronDoor& _Other) = delete;
	IronDoor& operator=(IronDoor&& _Other) noexcept = delete;

	IronDoorState GetCurState()
	{
		return m_CurState;
	}

	void SetEventColPos(float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 리셋 
	virtual void Reset() override;

	void DebugUpdate();

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 리소스 로드및생성
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_OpenEventCol = nullptr;
	std::shared_ptr<class DoorEffect> m_Effect = nullptr;

private:
	float m_RenderPivotY = 62.0f;
	float m_RenderPivotX = 25.0f;
	float m_ColPivot = 100.0f;
	float4 m_ColScale = { 50.0f, 200.0f , 1.0f };

	// 상태값 변경
	void ChangeState(IronDoorState _State);
	// 현재 상태값에 따른 업데이트 
	void UpdateState(float _DeltaTime);

	IronDoorState m_CurState = IronDoorState::CLOSE;
	IronDoorState m_PrevState = IronDoorState::NONE;
	IronDoorState m_NextState = IronDoorState::NONE;

	void CloseStart();
	void CloseUpdate(float _DeltaTime);
	void CloseEnd();

	void OpenStart();
	void OpenUpdate(float _DeltaTime);
	void OpenEnd();
};

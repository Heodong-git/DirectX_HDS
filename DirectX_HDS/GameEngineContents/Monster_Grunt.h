#pragma once
#include "BaseActor.h"

enum class GruntState
{
	NONE,
	IDLE,	 // 아이들
	WALK,	 // 걷기
	CHASE,	 // 뛰기 
	HITGROUND,	 // 쳐맞음
	AIM,	 // 공격 
};

// 근육맨
class Monster_Grunt : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Grunt();
	~Monster_Grunt();

	// delete Function
	Monster_Grunt(const Monster_Grunt& _Other) = delete;
	Monster_Grunt(Monster_Grunt&& _Other) noexcept = delete;
	Monster_Grunt& operator=(const Monster_Grunt& _Other) = delete;
	Monster_Grunt& operator=(Monster_Grunt&& _Other) noexcept = delete;

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
	// 방향
	// + 오른쪽 
	// - 왼쪽
	int m_Direction = -1;
	void DirCheck();

	// 상태값 변경
	void ChangeState(GruntState _State);
	// 현재 상태값에 따른 업데이트 
	void UpdateState(float _DeltaTime);

	GruntState m_CurState = GruntState::NONE;
	GruntState m_PrevState = GruntState::NONE;
	GruntState m_NextState = GruntState::NONE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	void ChaseStart();
	void ChaseUpdate(float _DeltaTime);
	void ChaseEnd();

	void HitGroundStart();
	void HitGroundUpdate(float _DeltaTime);
	void HitGroundEnd();

};

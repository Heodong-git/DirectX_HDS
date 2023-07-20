#pragma once
#include "BaseActor.h"

enum class LaserState
{
	NONE,
	IDLE,
	COLLISION,
	RECORDING_PROGRESS,
	RECORDING_PROGRESS_FORWARD,
};


// 얘는 만들때, 스케일을 세팅해주면 탑의 위치를 스케일에 비례해서 자동으로 위쪽에 세팅되게.. 

// 설명 :
class Laser : public BaseActor
{
public:
	// constrcuter destructer
	Laser();
	~Laser();

	// delete Function
	Laser(const Laser& _Other) = delete;
	Laser(Laser&& _Other) noexcept = delete;
	Laser& operator=(const Laser& _Other) = delete;
	Laser& operator=(Laser&& _Other) noexcept = delete;

	// 그냥 SetScale을하면, 그 크기로 변경하고, 탑의 위치도 알아서 조정되는 걸로 바꿔 
	void SetLaserScale(float4& _Scale);

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

	std::shared_ptr<class GameEngineSpriteRenderer> m_TopRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_LaserRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// 스케일 
	float4 m_LaserScale = {};

	// 상태값 변경
	void ChangeState(LaserState _State);
	// 현재 상태값에 따른 업데이트 
	void UpdateState(float _DeltaTime);

	LaserState m_CurState = LaserState::IDLE;
	LaserState m_PrevState = LaserState::NONE;
	LaserState m_NextState = LaserState::NONE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void CollisionStart();
	void CollisionUpdate(float _DeltaTime);
	void CollisionEnd();
	
	void RecordingProgressStart();
	void RecordingProgressUpdate(float _DeltaTime);
	void RecordingProgressEnd();

	void RecordingProgress_ForwardStart();
	void RecordingProgress_ForwardUpdate(float _DeltaTime);
	void RecordingProgress_ForwardEnd();
};

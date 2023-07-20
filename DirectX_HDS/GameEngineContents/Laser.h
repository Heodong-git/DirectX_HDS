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


// ��� ���鶧, �������� �������ָ� ž�� ��ġ�� �����Ͽ� ����ؼ� �ڵ����� ���ʿ� ���õǰ�.. 

// ���� :
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

	// �׳� SetScale���ϸ�, �� ũ��� �����ϰ�, ž�� ��ġ�� �˾Ƽ� �����Ǵ� �ɷ� �ٲ� 
	void SetLaserScale(float4& _Scale);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	// ���� 
	virtual void Reset() override;

	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� ���ҽ� �ε�׻���
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_TopRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_LaserRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// ������ 
	float4 m_LaserScale = {};

	// ���°� ����
	void ChangeState(LaserState _State);
	// ���� ���°��� ���� ������Ʈ 
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

#pragma once
#include "BaseActor.h"

enum class LaserState
{
	NONE,
	IDLE,
	COLLISION,
};

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
	
};

#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Bullet : public BaseActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	inline void SetMoveDir(const float4& _Dir)
	{
		m_MoveDir = _Dir;
	}

	inline bool IsParring() const
	{
		return m_Parring;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	void DirCorrection();
	float4 m_MoveDir = {};
	float m_MoveSpeed = 1000.0f;
	float m_LiveTime = 5.0f;
	
	bool m_Parring = false;
	bool m_DirChange = false;
};

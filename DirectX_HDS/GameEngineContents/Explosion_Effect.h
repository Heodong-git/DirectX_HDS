#pragma once
#include "BaseActor.h"

enum class EffectType
{
	NONE,
	FIRST,
	SECOND,
	THIRD,
};


// Ό³Έν :
class Explosion_Effect : public BaseActor
{
public:
	// constrcuter destructer
	Explosion_Effect();
	~Explosion_Effect();

	// delete Function
	Explosion_Effect(const Explosion_Effect& _Other) = delete;
	Explosion_Effect(Explosion_Effect&& _Other) noexcept = delete;
	Explosion_Effect& operator=(const Explosion_Effect& _Other) = delete;
	Explosion_Effect& operator=(Explosion_Effect&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_Render;
	}

	void SetType(EffectType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
};

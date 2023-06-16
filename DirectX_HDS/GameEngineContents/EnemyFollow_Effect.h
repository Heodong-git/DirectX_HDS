#pragma once
#include "BaseActor.h"

// Ό³Έν :
class EnemyFollow_Effect : public BaseActor
{
public:
	// constrcuter destructer
	EnemyFollow_Effect();
	~EnemyFollow_Effect();

	// delete Function
	EnemyFollow_Effect(const EnemyFollow_Effect& _Other) = delete;
	EnemyFollow_Effect(EnemyFollow_Effect&& _Other) noexcept = delete;
	EnemyFollow_Effect& operator=(const EnemyFollow_Effect& _Other) = delete;
	EnemyFollow_Effect& operator=(EnemyFollow_Effect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

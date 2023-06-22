#pragma once
#include "BaseActor.h"

// Ό³Έν :
class HeadHunter_RifleEffect : public BaseActor
{
public:
	// constrcuter destructer
	HeadHunter_RifleEffect();
	~HeadHunter_RifleEffect();

	// delete Function
	HeadHunter_RifleEffect(const HeadHunter_RifleEffect& _Other) = delete;
	HeadHunter_RifleEffect(HeadHunter_RifleEffect&& _Other) noexcept = delete;
	HeadHunter_RifleEffect& operator=(const HeadHunter_RifleEffect& _Other) = delete;
	HeadHunter_RifleEffect& operator=(HeadHunter_RifleEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
};

#pragma once
#include "BaseActor.h"

// Ό³Έν :
class LandEffect : public BaseActor
{
public:
	// constrcuter destructer
	LandEffect();
	~LandEffect();

	// delete Function
	LandEffect(const LandEffect& _Other) = delete;
	LandEffect(LandEffect&& _Other) noexcept = delete;
	LandEffect& operator=(const LandEffect& _Other) = delete;
	LandEffect& operator=(LandEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

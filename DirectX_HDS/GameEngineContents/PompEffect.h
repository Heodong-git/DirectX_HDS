#pragma once
#include "BaseActor.h"

// Ό³Έν :
class PompEffect : public BaseActor
{
public:
	// constrcuter destructer
	PompEffect();
	~PompEffect();

	// delete Function
	PompEffect(const PompEffect& _Other) = delete;
	PompEffect(PompEffect&& _Other) noexcept = delete;
	PompEffect& operator=(const PompEffect& _Other) = delete;
	PompEffect& operator=(PompEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

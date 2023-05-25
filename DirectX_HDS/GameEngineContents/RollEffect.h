#pragma once
#include "BaseActor.h"

// Ό³Έν :
class RollEffect : public BaseActor
{
public:
	// constrcuter destructer
	RollEffect();
	~RollEffect();

	// delete Function
	RollEffect(const RollEffect& _Other) = delete;
	RollEffect(RollEffect&& _Other) noexcept = delete;
	RollEffect& operator=(const RollEffect& _Other) = delete;
	RollEffect& operator=(RollEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

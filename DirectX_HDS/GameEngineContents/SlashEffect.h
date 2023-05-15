#pragma once
#include "BaseActor.h"

// Ό³Έν :
class SlashEffect : public BaseActor
{
public:
	// constrcuter destructer
	SlashEffect();
	~SlashEffect();

	// delete Function
	SlashEffect(const SlashEffect& _Other) = delete;
	SlashEffect(SlashEffect&& _Other) noexcept = delete;
	SlashEffect& operator=(const SlashEffect& _Other) = delete;
	SlashEffect& operator=(SlashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

#pragma once
#include "BaseActor.h"

// Ό³Έν :
class DashEffect : public BaseActor
{
public:
	// constrcuter destructer
	DashEffect();
	~DashEffect();

	// delete Function
	DashEffect(const DashEffect& _Other) = delete;
	DashEffect(DashEffect&& _Other) noexcept = delete;
	DashEffect& operator=(const DashEffect& _Other) = delete;
	DashEffect& operator=(DashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

#pragma once
#include "BaseActor.h"

// Ό³Έν :
class FireEffect : public BaseActor
{
public:
	// constrcuter destructer
	FireEffect();
	~FireEffect();

	// delete Function
	FireEffect(const FireEffect& _Other) = delete;
	FireEffect(FireEffect&& _Other) noexcept = delete;
	FireEffect& operator=(const FireEffect& _Other) = delete;
	FireEffect& operator=(FireEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

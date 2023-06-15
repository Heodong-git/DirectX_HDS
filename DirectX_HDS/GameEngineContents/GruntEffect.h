#pragma once
#include "BaseActor.h"

// Ό³Έν :
class GruntEffect : public BaseActor
{
public:
	// constrcuter destructer
	GruntEffect();
	~GruntEffect();

	// delete Function
	GruntEffect(const GruntEffect& _Other) = delete;
	GruntEffect(GruntEffect&& _Other) noexcept = delete;
	GruntEffect& operator=(const GruntEffect& _Other) = delete;
	GruntEffect& operator=(GruntEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

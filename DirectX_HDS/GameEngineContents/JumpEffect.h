#pragma once
#include "BaseActor.h"

// Ό³Έν :
class JumpEffect : public BaseActor
{
public:
	// constrcuter destructer
	JumpEffect();
	~JumpEffect();

	// delete Function
	JumpEffect(const JumpEffect& _Other) = delete;
	JumpEffect(JumpEffect&& _Other) noexcept = delete;
	JumpEffect& operator=(const JumpEffect& _Other) = delete;
	JumpEffect& operator=(JumpEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

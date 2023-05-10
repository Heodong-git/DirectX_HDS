#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class Inven : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	Inven();
	~Inven();

	// delete Function
	Inven(const Inven& _Other) = delete;
	Inven(Inven&& _Other) noexcept = delete;
	Inven& operator=(const Inven& _Other) = delete;
	Inven& operator=(Inven&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_CaseRender = nullptr;
};

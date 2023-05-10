#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class Battery : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	Battery();
	~Battery();

	// delete Function
	Battery(const Battery& _Other) = delete;
	Battery(Battery&& _Other) noexcept = delete;
	Battery& operator=(const Battery& _Other) = delete;
	Battery& operator=(Battery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_CaseRender = nullptr;
};

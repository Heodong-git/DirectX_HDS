#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class CBattery : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CBattery();
	~CBattery();

	// delete Function
	CBattery(const CBattery& _Other) = delete;
	CBattery(CBattery&& _Other) noexcept = delete;
	CBattery& operator=(const CBattery& _Other) = delete;
	CBattery& operator=(CBattery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_CaseRender = nullptr;
};

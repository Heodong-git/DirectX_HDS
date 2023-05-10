#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class Hud : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	Hud();
	~Hud();

	// delete Function
	Hud(const Hud& _Other) = delete;
	Hud(Hud&& _Other) noexcept = delete;
	Hud& operator=(const Hud& _Other) = delete;
	Hud& operator=(Hud&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
};

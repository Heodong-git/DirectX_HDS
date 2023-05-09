#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class CHud : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CHud();
	~CHud();

	// delete Function
	CHud(const CHud& _Other) = delete;
	CHud(CHud&& _Other) noexcept = delete;
	CHud& operator=(const CHud& _Other) = delete;
	CHud& operator=(CHud&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
};

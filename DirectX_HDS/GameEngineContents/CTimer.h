#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class CTimer : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CTimer();
	~CTimer();

	// delete Function
	CTimer(const CTimer& _Other) = delete;
	CTimer(CTimer&& _Other) noexcept = delete;
	CTimer& operator=(const CTimer& _Other) = delete;
	CTimer& operator=(CTimer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_CaseRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_GageRender = nullptr;
};

#pragma once
#include "CKatanaZero_Actor.h"

// Ό³Έν :
class CInven : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CInven();
	~CInven();

	// delete Function
	CInven(const CInven& _Other) = delete;
	CInven(CInven&& _Other) noexcept = delete;
	CInven& operator=(const CInven& _Other) = delete;
	CInven& operator=(CInven&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_CaseRender = nullptr;
};

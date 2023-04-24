#pragma once
#include "CKatanaZero_Actor.h"

// º¸½º 
class CBoss_HeadHunter : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CBoss_HeadHunter();
	~CBoss_HeadHunter();

	// delete Function
	CBoss_HeadHunter(const CBoss_HeadHunter& _Other) = delete;
	CBoss_HeadHunter(CBoss_HeadHunter&& _Other) noexcept = delete;
	CBoss_HeadHunter& operator=(const CBoss_HeadHunter& _Other) = delete;
	CBoss_HeadHunter& operator=(CBoss_HeadHunter&& _Other) noexcept = delete;


	float4 TestColor;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineRenderer> Render0;
	float4 m_Scale = { 75.0f , 75.0f , 0.0f };
};

#pragma once
#include "BaseActor.h"

// 설명 :
class SlashHit_Effect : public BaseActor
{
public:
	// constrcuter destructer
	SlashHit_Effect();
	~SlashHit_Effect();

	// delete Function
	SlashHit_Effect(const SlashHit_Effect& _Other) = delete;
	SlashHit_Effect(SlashHit_Effect&& _Other) noexcept = delete;
	SlashHit_Effect& operator=(const SlashHit_Effect& _Other) = delete;
	SlashHit_Effect& operator=(SlashHit_Effect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 렌더러생성 및 세팅
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;

};

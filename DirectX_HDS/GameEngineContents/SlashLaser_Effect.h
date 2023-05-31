#pragma once
#include "BaseActor.h"

// 설명 :
class SlashLaser_Effect : public BaseActor
{
public:
	// constrcuter destructer
	SlashLaser_Effect();
	~SlashLaser_Effect();

	// delete Function
	SlashLaser_Effect(const SlashLaser_Effect& _Other) = delete;
	SlashLaser_Effect(SlashLaser_Effect&& _Other) noexcept = delete;
	SlashLaser_Effect& operator=(const SlashLaser_Effect& _Other) = delete;
	SlashLaser_Effect& operator=(SlashLaser_Effect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 렌더러생성 및 세팅
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

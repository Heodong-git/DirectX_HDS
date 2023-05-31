#pragma once
#include "BaseActor.h"

// ���� :
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
	// ���������� �� ����
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

#pragma once
#include "BaseActor.h"

// ���� :
class DoorEffect : public BaseActor
{
public:
	// constrcuter destructer
	DoorEffect();
	~DoorEffect();

	// delete Function
	DoorEffect(const DoorEffect& _Other) = delete;
	DoorEffect(DoorEffect&& _Other) noexcept = delete;
	DoorEffect& operator=(const DoorEffect& _Other) = delete;
	DoorEffect& operator=(DoorEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float m_RenderTime = 1.0f;
	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
};

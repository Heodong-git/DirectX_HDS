#pragma once
#include "BaseActor.h"

// ���� :
class LaserSwitch : public BaseActor
{
public:
	// constrcuter destructer
	LaserSwitch();
	~LaserSwitch();

	// delete Function
	LaserSwitch(const LaserSwitch& _Other) = delete;
	LaserSwitch(LaserSwitch&& _Other) noexcept = delete;
	LaserSwitch& operator=(const LaserSwitch& _Other) = delete;
	LaserSwitch& operator=(LaserSwitch&& _Other) noexcept = delete;

	// push laser 
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// �÷��̾ �浹���� ���¿��� Ư�� Ű �Է½� ����ġ �¿��� 
	bool m_IsOn = true;
	// ����ġ
	void LaserSwitchButton()
	{
		m_IsOn = !m_IsOn;
	}

	// ���� 
	virtual void Reset() override;

	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� ���ҽ� �ε�׻���
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_SwitchRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::vector<std::shared_ptr<class Laser>> m_Lasers = std::vector<std::shared_ptr<class Laser>>();

};

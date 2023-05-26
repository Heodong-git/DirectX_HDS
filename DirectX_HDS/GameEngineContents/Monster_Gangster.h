#pragma once
#include "BaseActor.h"

// ������ 
class Monster_Gangster : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Gangster();
	~Monster_Gangster();

	// delete Function
	Monster_Gangster(const Monster_Gangster& _Other) = delete;
	Monster_Gangster(Monster_Gangster&& _Other) noexcept = delete;
	Monster_Gangster& operator=(const Monster_Gangster& _Other) = delete;
	Monster_Gangster& operator=(Monster_Gangster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� ���ҽ� �ε�׻���
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
};

#pragma once
#include "BaseActor.h"

// ���� :
class FanBlade : public BaseActor
{
public:
	// constrcuter destructer
	FanBlade();
	~FanBlade();

	// delete Function
	FanBlade(const FanBlade& _Other) = delete;
	FanBlade(FanBlade&& _Other) noexcept = delete;
	FanBlade& operator=(const FanBlade& _Other) = delete;
	FanBlade& operator=(FanBlade&& _Other) noexcept = delete;

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

	std::shared_ptr<class GameEngineSpriteRenderer> m_CoverRender_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_CoverRender_Right = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_FanRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

};

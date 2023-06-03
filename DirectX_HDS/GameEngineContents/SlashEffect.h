#pragma once
#include "BaseActor.h"

// 설명 :
class SlashEffect : public BaseActor
{
public:
	// constrcuter destructer
	SlashEffect();
	~SlashEffect();

	// delete Function
	SlashEffect(const SlashEffect& _Other) = delete;
	SlashEffect(SlashEffect&& _Other) noexcept = delete;
	SlashEffect& operator=(const SlashEffect& _Other) = delete;
	SlashEffect& operator=(SlashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();

	// 렌더러생성 및 세팅
	void ComponentSetting();
	void CollisionUpdate(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	const float m_RenderPivot = 40.0f;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	const float4 m_ColScale = { 100.0f , 60.0f };
	float  m_ColPivot = 30.0f;
	float m_Angle = 0.0f;

	float4 m_AttPos = float4::Null;
	float4 m_PlayerPos = float4::Null;
};

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

	inline void SetMovePos(float4& _Pos)
	{
		m_MovePos = _Pos;
	}

	inline void SetAngle(const float _Angle)
	{
		m_Angle = _Angle;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float m_MoveSpeed = 15000.0f;
	float m_Angle = 0.0f;
	void MoveUpdate(float _DeltaTime);
	float4 m_MovePos = {};
	// 렌더러생성 및 세팅
	void ComponentSetting();
	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
};

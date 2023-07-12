#pragma once
#include "BaseActor.h"

enum class TrailType
{
	NONE,
	PLAYER,
	BOSS,
};

// 보류 

// 설명 :
class Trail_Effect : public BaseActor
{
public:
	// constrcuter destructer
	Trail_Effect();
	~Trail_Effect();

	// delete Function
	Trail_Effect(const Trail_Effect& _Other) = delete;
	Trail_Effect(Trail_Effect&& _Other) noexcept = delete;
	Trail_Effect& operator=(const Trail_Effect& _Other) = delete;
	Trail_Effect& operator=(Trail_Effect&& _Other) noexcept = delete;

	void SetTexture(std::string_view _Name, float4& _Size, TrailType _Type);
	inline void SetType(TrailType _Type)
	{
		m_Type = _Type;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	TrailType m_Type = TrailType::NONE;
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;

	const float m_MaxLivetime = 0.08f;
	const float4 m_PlayerRenderPivot = float4{ 0.0f, 36.0f, -1.0f };
	const float4 m_HeadHunterRenderPivot = float4{ 0.0f, 42.0f , -1.0f };
};

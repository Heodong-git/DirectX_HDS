#pragma once
#include "BaseActor.h"

// Ό³Έν :
class GunSpark_Effect : public BaseActor
{
public:
	// constrcuter destructer
	GunSpark_Effect();
	~GunSpark_Effect();

	// delete Function
	GunSpark_Effect(const GunSpark_Effect& _Other) = delete;
	GunSpark_Effect(GunSpark_Effect&& _Other) noexcept = delete;
	GunSpark_Effect& operator=(const GunSpark_Effect& _Other) = delete;
	GunSpark_Effect& operator=(GunSpark_Effect&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_Render;
	}

	void SetAngle(const float _Angle)
	{
		m_Angle;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	float m_Angle = 0.0f;
};

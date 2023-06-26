#pragma once
#include "BaseActor.h"

enum class EffectType
{
	NONE,
	FIRST,
	SECOND,
	THIRD,
};

// Ό³Έν :
class GunSmoke_Effect : public BaseActor
{
public:
	// constrcuter destructer
	GunSmoke_Effect();
	~GunSmoke_Effect();

	// delete Function
	GunSmoke_Effect(const GunSmoke_Effect& _Other) = delete;
	GunSmoke_Effect(GunSmoke_Effect&& _Other) noexcept = delete;
	GunSmoke_Effect& operator=(const GunSmoke_Effect& _Other) = delete;
	GunSmoke_Effect& operator=(GunSmoke_Effect&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_Render;
	}


	void SetType(EffectType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};

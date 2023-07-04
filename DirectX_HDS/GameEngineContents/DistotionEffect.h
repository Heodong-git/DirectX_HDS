#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// Ό³Έν :
class DistotionEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	DistotionEffect();
	~DistotionEffect();

	// delete Function
	DistotionEffect(const DistotionEffect& _Other) = delete;
	DistotionEffect(DistotionEffect&& _Other) noexcept = delete;
	DistotionEffect& operator=(const DistotionEffect& _Other) = delete;
	DistotionEffect& operator=(DistotionEffect&& _Other) noexcept = delete;

	void EffectOn()
	{
		m_IsUpdate = true;
	}

	void EffectOff()
	{
		m_IsUpdate = false;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	RenderBaseValue BaseValue;
	std::shared_ptr<GameEngineRenderUnit> BlurUnit;
	bool m_IsUpdate = false;
};

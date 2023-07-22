#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// Ό³Έν :
class KatanaFadeEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	KatanaFadeEffect();
	~KatanaFadeEffect();

	// delete Function
	KatanaFadeEffect(const KatanaFadeEffect& _Other) = delete;
	KatanaFadeEffect(KatanaFadeEffect&& _Other) noexcept = delete;
	KatanaFadeEffect& operator=(const KatanaFadeEffect& _Other) = delete;
	KatanaFadeEffect& operator=(KatanaFadeEffect&& _Other) noexcept = delete;

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
	std::shared_ptr<GameEngineRenderUnit> FadeUnit;
	bool m_IsUpdate = false;
};

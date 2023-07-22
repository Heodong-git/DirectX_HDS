#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class GlitchState
{
	NONE,
	ON,
	OFF,
};

// Ό³Έν :
class GlitchEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	GlitchEffect();
	~GlitchEffect();

	// delete Function
	GlitchEffect(const GlitchEffect& _Other) = delete;
	GlitchEffect(GlitchEffect&& _Other) noexcept = delete;
	GlitchEffect& operator=(const GlitchEffect& _Other) = delete;
	GlitchEffect& operator=(GlitchEffect&& _Other) noexcept = delete;

	void EffectOn()
	{
		m_Update = true;
	}

	void EffectOff()
	{
		m_Update = false;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	RenderBaseValue BaseValue;
	GlitchState State = GlitchState::NONE;
	std::shared_ptr<GameEngineRenderUnit> GlitchUnit;
	float m_EffectTime = 0.6f;
	bool m_Update = false;
};

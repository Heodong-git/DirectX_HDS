#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// ���� :
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

	inline const float GetEffectTime()
	{
		return m_EffectTime;
	}

	void EffectOn()
	{
		m_IsUpdate = true;
		m_EffectTime = 1.2f;
	}

	void EffectOff()
	{
		m_IsUpdate = false;
	}

	const bool IsComplete() const
	{
		return m_Complete;							
	}
	

	inline const bool IsUpdate()
	{
		return m_IsUpdate;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	RenderBaseValue BaseValue;
	std::shared_ptr<GameEngineRenderUnit> FadeUnit;
	float m_EffectTime = 0.0f;
	bool m_IsUpdate = false;
	bool m_Complete = false;
};

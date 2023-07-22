#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineSprite.h>

// 카메라를 1개 더만들고 말지.
// 설명 :
class OldFilmEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	OldFilmEffect();
	~OldFilmEffect();

	// delete Function
	OldFilmEffect(const OldFilmEffect& _Other) = delete;
	OldFilmEffect(OldFilmEffect&& _Other) noexcept = delete;
	OldFilmEffect& operator=(const OldFilmEffect& _Other) = delete;
	OldFilmEffect& operator=(OldFilmEffect&& _Other) noexcept = delete;

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
	std::shared_ptr<GameEngineRenderUnit> OldUnit;
	std::shared_ptr<GameEngineSprite> OldSprite;

	float4 OldData;
	bool m_Update = false;

	int Index = 0;
};


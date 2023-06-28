#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class FadeState
{
	NONE,
	FADEIN,
	FADEOUT,
};

// Ό³Έν :
class FadeEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	FadeEffect();
	~FadeEffect();

	// delete Function
	FadeEffect(const FadeEffect& _Other) = delete;
	FadeEffect(FadeEffect&& _Other) noexcept = delete;
	FadeEffect& operator=(const FadeEffect& _Other) = delete;
	FadeEffect& operator=(FadeEffect&& _Other) noexcept = delete;

	void FadeIn()
	{
		// 0.0f 
		State = FadeState::FADEIN;
		FadeData.x = 0.1f;
	}

	void FadeOut()
	{
		State = FadeState::FADEOUT;
		FadeData.x = 1.0f;
	}

	FadeState GetState()
	{
		return State;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	float4 FadeData = { 1.0f, 1.0f, 1.0f, 1.0f };
	FadeState State = FadeState::NONE;
	std::shared_ptr<GameEngineRenderUnit> FadeUnit;
};


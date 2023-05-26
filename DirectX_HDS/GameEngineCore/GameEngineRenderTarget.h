#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"

class GameEngineRenderTarget;
class GameEnginePostProcess
	: std::enable_shared_from_this<GameEnginePostProcess>
{
	friend GameEngineRenderTarget;

public:
	std::shared_ptr<GameEngineRenderTarget> ResultTarget;

protected:
	virtual void Start(std::shared_ptr<GameEngineRenderTarget> _Target) = 0;
	virtual void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) = 0;
};

// 설명 :
class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget> ,
	std::enable_shared_from_this<GameEngineRenderTarget>
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::Create(_Name);

		NewRenderTarget->ResCreate(_Texture, _Color);

		return NewRenderTarget;
	}

	static std::shared_ptr<GameEngineRenderTarget> Create(DXGI_FORMAT _Format, float4 _Scale, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::CreateUnNamed();

		NewRenderTarget->ResCreate(_Format, _Scale, _Color);

		return NewRenderTarget;
	}

	void Clear();

	void Setting() override;
	
	// GameEngineVideo 테스트용 함수
	void Reset();

	void CreateDepthTexture(int _Index = 0);

	void Merge(std::shared_ptr<GameEngineRenderTarget> _Other, size_t _Index = 0);

	// 렌더타겟에 이펙트를 추가한다는 개념
	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect()
	{
		std::shared_ptr<EffectType> Effect = std::make_shared<EffectType>();
		std::shared_ptr<GameEnginePostProcess> UpCast = std::dynamic_pointer_cast<GameEnginePostProcess>(Effect);
		// UpCast->Start((shared_from_this()));
		Effects.push_back(Effect);
		return Effect;
	}

	void Effect();

protected:

private:
	static void RenderTargetUnitInit();
	static GameEngineRenderUnit MergeUnit;

	float4 Color = { 0.0f, 0.0f, 0.0f, 0.0f };

	std::vector<std::shared_ptr<GameEnginePostProcess>> Effects;
	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTVs;

	// 깊이버퍼용 텍스쳐
	std::shared_ptr<GameEngineTexture> DepthTexture;
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

	void ResCreate(DXGI_FORMAT _Format, float4 _Scale, float4 _Color);
};


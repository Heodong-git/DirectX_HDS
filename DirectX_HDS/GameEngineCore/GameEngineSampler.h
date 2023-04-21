#pragma once
#include "GameEngineResource.h"

// 설명 : 텍스쳐의 색깔을 받아오기위한 옵션을 담은녀석을 샘플러라고 한다. 
class GameEngineSampler : public GameEngineResource<GameEngineSampler>
{
	friend class GameEngineSamplerSetter;

public:
	// constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete Function
	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineSampler> Create(const std::string_view& _Name, const D3D11_SAMPLER_DESC& Desc)
	{
		std::shared_ptr<GameEngineSampler> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(Desc);
		return NewTexture;
	}

protected:

private:
	ID3D11SamplerState* State;
	D3D11_SAMPLER_DESC Desc{};

	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};


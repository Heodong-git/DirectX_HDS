#pragma once
#include "GameEngineResource.h"

// WINAPI 의 IMAGE
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;

public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RenderTarget;
	}

protected:

private:
	// HIBITMAP 
	ID3D11Texture2D* Texture2D = nullptr;
	// HDC : 비트맵에 그릴수 있는 권한, 이 한묶음의 세트가 그대로 다이렉트버전으로 변경됐다고 보면 됨 
	ID3D11RenderTargetView* RenderTarget = nullptr;

	void Create(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();

};


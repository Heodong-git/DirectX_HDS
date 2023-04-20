#pragma once
#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

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

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return Load(_Path, NewPath.GetFileName());
	}

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResLoad(_Path);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
		return NewTexture;
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

	void ResLoad(const std::string_view& _Path);
	void ResCreate(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();

};


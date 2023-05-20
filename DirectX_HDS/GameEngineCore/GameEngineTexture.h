#pragma once
#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>

class GameEnginePixelColor
{
public:
	static GameEnginePixelColor Black;

	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned char ColorChar[4];
		int Color;
	};

	bool operator==(GameEnginePixelColor _Color)
	{
		return Color == _Color.Color;
	}

	float4 Tofloat4()
	{

	}

	// 변수초기화
	GameEnginePixelColor()
	{

	}

	GameEnginePixelColor(char _r, char _g, char _b, char _a)
		: r(_r), g(_g), b(_b), a(_a)
	{

	}
};



// WINAPI 의 IMAGE
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;
	friend class GameEngineTextureSetter;

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

	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::CreateUnNamed();
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}

	int GetWidth()
	{
		return Desc.Width;
	}

	int GetHeight()
	{
		return Desc.Height;
	}

	float4 GetScale()
	{
		return float4(static_cast<float>(Desc.Width), static_cast<float>(Desc.Height));
	}

	GameEnginePixelColor GetPixel(int _X, int _Y, GameEnginePixelColor DefaultColor = GameEnginePixelColor::Black);

protected:

private:
	// HIBITMAP 
	ID3D11Texture2D* Texture2D = nullptr;
	// HDC : 비트맵에 그릴수 있는 권한, 이 한묶음의 세트가 그대로 다이렉트버전으로 변경됐다고 보면 됨 
	ID3D11RenderTargetView* RTV = nullptr;
	ID3D11DepthStencilView* DSV = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data = {};
	DirectX::ScratchImage Image = {};

	void ResLoad(const std::string_view& _Path);
	void ResCreate(ID3D11Texture2D* _Value);

	void ResCreate(const D3D11_TEXTURE2D_DESC& _Value);

	void CreateRenderTargetView();
	void CreateShaderResourcesView();
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};


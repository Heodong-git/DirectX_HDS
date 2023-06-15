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

	GameEnginePixelColor(unsigned char  _r, unsigned char  _g, unsigned char  _b, unsigned char  _a)
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

	// 경로체크 
	static void PathCheck(const std::string_view& _Path, const std::string_view& _Name);

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);

		// 리소스 로드 시에 경로를 체크해준다 
		PathCheck(_Path, _Name);
		NewTexture->SetPath(_Path);
		NewTexture->ResLoad(_Path);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::CreateUnNamed();
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> UnLoad(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Find(_Name);

		if (nullptr == NewTexture)
		{
			MsgAssert("존재하지 않는 텍스처를 언로드 하려고 했습니다.");
		}

		NewTexture->Release();
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> ReLoad(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return ReLoad(_Path, NewPath.GetFileName());
	}


	static std::shared_ptr<GameEngineTexture> ReLoad(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource<GameEngineTexture>::Find(_Name);

		if (nullptr == NewTexture)
		{
			MsgAssert("존재하지 않는 텍스처를 로드 하려고 했습니다.");
		}

		NewTexture->ReLoad();
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

	void ReLoad();
	void Release();

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


	// 카메라 렌더타겟의 에러를 해결하기 위해
	void VSReset(UINT _Slot);
	void PSReset(UINT _Slot);
};


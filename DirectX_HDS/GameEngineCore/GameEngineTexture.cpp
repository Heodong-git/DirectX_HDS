#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Release\\DirectXTex.lib")
#endif

// #pragma comment(lib, "DirectXTex.lib")

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}


void GameEngineTexture::ResCreate(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	CreateRenderTargetView();
}

void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟을 만들 수는 없습니다.");
		return;
	}

	// 랜더타겟은 여러개를 만들수 있다.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}

}


void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
	// GameEnginePath NewPath = 

	GameEnginePath NewPath(_Path);

	std::string Ext = GameEngineString::ToUpper(NewPath.GetExtension());

	std::wstring Path = GameEngineString::AnsiToUniCode(NewPath.GetFullPath());

	if (Ext == ".TGA")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}
	else if (Ext == ".DDS")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}
	else if (S_OK != DirectX::LoadFromWICFile(Path.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineDevice::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgAssert("쉐이더 리소스 뷰 생성에 실패했습니다." + std::string(_Path.data()));
	}

}

void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

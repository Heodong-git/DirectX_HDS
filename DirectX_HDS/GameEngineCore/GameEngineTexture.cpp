#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != RenderTarget)
	{
		RenderTarget->Release();
		RenderTarget = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}


void GameEngineTexture::Create(ID3D11Texture2D* _Create)
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
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTarget);

	if (S_OK != Result)
	{
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}

}

#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
}


void GameEngineRenderTarget::Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	Color = _Color;
	Texture = _Texture;
}

void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);
}
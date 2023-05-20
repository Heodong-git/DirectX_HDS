#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
	DepthTexture = nullptr;
}


void GameEngineRenderTarget::ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	Color = _Color;
	Texture = _Texture;
}

void GameEngineRenderTarget::ResCreate(float4 _Color)
{
}

void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
		return;
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);

	ID3D11DepthStencilView* DSV
		= DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	if (nullptr != DSV)
	{
		GameEngineDevice::GetContext()->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void GameEngineRenderTarget::Setting()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
	}

	ID3D11DepthStencilView* DSV
		= DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	// 현시점에서는 z 값 사용 X 
	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, DSV);
}

// test용 함수, 삭제할수도있음
void GameEngineRenderTarget::Reset()
{
	ID3D11RenderTargetView* RTV[8] = { nullptr };

	GameEngineDevice::GetContext()->OMSetRenderTargets(8, RTV, nullptr);
}

void GameEngineRenderTarget::CreateDepthTexture()
{
	D3D11_TEXTURE2D_DESC Desc = { 0, };

	Desc.ArraySize = 1;
	Desc.Width = Texture->GetWidth();
	Desc.Height = Texture->GetHeight();

	//            4바이트중 3바이트는 0~1.0f 표현하는데 사용하고
	//            나머지 뒤에있는 1바이트를 스텐실 값이라고 하는 걸로 사용할수 있게 하는 포맷
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	DepthTexture = GameEngineTexture::Create(Desc);
}
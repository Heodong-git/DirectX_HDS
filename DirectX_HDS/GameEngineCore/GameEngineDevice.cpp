#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

// static 변수 구현
ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;

GameEngineDevice::GameEngineDevice()
{
}

GameEngineDevice::~GameEngineDevice()
{
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	// GDI+ DXGI <=
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// c++에서 지원하는 클래스를 구분하기 위한 GUI를 얻어온다. 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	// 그래픽카드가 2개일 경우를 대비
	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Adapterindex, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();

	return Adapter;

}

void GameEngineDevice::CreateSwapChain()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };

	// 기본정보
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();

	// 화면 갱신률
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;

	// 그래픽이미지 포맷
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 이 스왑체인은 단순히 
	// DXGI_USAGE_RENDER_TARGET_OUTPUT 윈도우에 띄워주는 용도로 만들것이다.
	// 쉐이더에서도 이걸 사용할수 있게 하겠다.
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// 안티앨리어싱 자동추가 
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
}

// 디바이스초기화
void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetHWnd())
	{ 
		MsgAssert("윈도우가 만들어지지 않았는데 디바이스를 초가화 할 수는 없습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// 다이렉트X 도 디버그 기능을 지원
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드와 직접 연결되는 인터페이스
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다.");
		return;
	}

	// CPU로 그린다. 
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE

	// 그래픽카드로 찾아서 그린다 
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE

	// 소프트웨어 디벨롭먼트 키트
	// 개발자에게 제공되는 lib , header 등의 총집합을 SDK 라고 한다. 

	// D3D11_SDK_VERSION 그냥 이 윈도우에서 지원하는 sdk 버전이 define

	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	// 최종적으로 결정된 다이렉트 레벨이 여기로 넘어올 것이다.
	// Level

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	// 윈도우와 연결하는 작업, 백버퍼를 만드는 작업을 수행
	CreateSwapChain();
}

void GameEngineDevice::Release()
{
	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}
}
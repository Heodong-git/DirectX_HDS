#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

class GameEngineDevice
{
public:
	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	static void Initialize();
	static void CreateSwapChain();
	static void Release();

	static void RenderStart();

	static void RenderEnd();

	static ID3D11Device* GetDevice()
	{
		return Device;
	}

	static ID3D11DeviceContext* GetContext()
	{
		return Context;
	}


	// HWND
protected:

private:
	// 다이렉트9에서는 Device 포인터로 모든 함수를 호출함.
	// ID3D9Device*

	// 다이렉트11 부터는 2가지로 인터페이스가 분리되었다.
	// 1. 리소스는 디바이스 인터페이스가 있다. 그래픽카드의 ram에 해당하는 부분에 대한 권한은 Device
	static ID3D11Device* Device;

	// 2. 렌더링에 관련된 연산은 context 
	static ID3D11DeviceContext* Context;

	// 3. 윈도우를 여러개 띄울수 있는 것처럼
	//    다이렉트 x를 사용하는 화면도 여러개를 띄울수가 있는데 그 화면 1개를 담당하는 API로 치자면 백버퍼DC1개가 SwapChain
	static IDXGISwapChain* SwapChain;
	static IDXGIAdapter* GetHighPerformanceAdapter();

	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();
};


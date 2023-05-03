#pragma once
#include <string>
#include <Windows.h>
#include <functional>
#include <GameEngineBase/GameEngineMath.h>

// 윈도우는 핸들 방식이라는것을 이용한다.
// 핸들방식이란 우리에게 os가 관리한다는 증명으로 숫자 1을 준다. 
// 그 숫자를 핸들이라고 한다. 

class GameEngineImage;
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	static std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> UserMessageFunction;
public:
	// 사용할 함수를 Window의 함수포인터에 세팅 
	static void SetUserMessageFunction(std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> _UserMessageFunction)
	{
		UserMessageFunction = _UserMessageFunction;
	}

	// 윈도우 생성
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);
	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	// 스크린사이즈 반환
	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	static HWND GetHWnd() 
	{
		return HWnd;
	}

	static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	static void AppOff()
	{
		IsWindowUpdate = false;
	}

	static void DoubleBufferClear();
	static void DoubleBufferRender();

	// functional 을 사용한 방식, 외부함수를 받아서 실행시켜준다. 
	static int WindowLoop(
		std::function<void()> _Start, 
		std::function<void()> _Loop, 
		std::function<void()> _End
	);

	// 마우스포지션 반환
	static float4 GetMousePosition();

	static void Release();

	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	

protected:

private:
	// 편리한 사용을 위해 모두 static 구현
	static float4 WindowSize;
	static float4 ScreenSize;
	static float4 WindowPos;
	static HWND HWnd;
	static HDC WindowBackBufferHdc; 
	static GameEngineImage* BackBufferImage;
	static GameEngineImage* DoubleBufferImage;
	static bool IsWindowUpdate;

	// 
	static WNDCLASSEX wcex;
};


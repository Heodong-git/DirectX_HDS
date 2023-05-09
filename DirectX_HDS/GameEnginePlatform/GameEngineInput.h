 #pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

private:
	class GameEngineKey 
	{
		friend GameEngineInput;

		bool Down = false; 
		bool Press = false; 
		bool Up = false; 
		bool Free = true; 

		// 눌린시간 
		float PressTime = 0.0f; 
		int Key = -1;

		void Reset()
		{
			Down = false; // 누른 한순간
			Press = false; // 계속 누르고 있다.
			Up = false; // 땐 한순간
			Free = true; // 안눌리고 있다.
		}

		bool KeyCheck() 
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);
	static void CreateKey(const std::string_view& _Name, int _Key);

	// 인자로 들어온 문자열로 생성된 키가 있는지 체크
	static bool IsKey(const std::string_view& _Name);

	// 현재 키가 어떤상태인지
	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);

	// 눌린시간 체크
	static float GetPressTime(const std::string_view& _Name);

	static void MouseCursorOff();

	// 현재 아무키가 눌렸는지 체크
	static bool IsAnyKey() 
	{
		return IsAnyKeyValue;
	}

	static float4 GetMousePosition()
	{
		return MousePos;
	}

	static float4 GetMouseDirection()
	{
		return MouseDirection;
	}

	static float4 GetMouseDirectionNormal()
	{
		return MouseDirection.NormalizeReturn();
	}

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;
	static bool IsAnyKeyValue;
	static bool IsFocus;

	static float4 MousePos;
	static float4 PrevMousePos;
	static float4 MouseDirection;

	static void IsFocusOn()
	{
		IsFocus = true;
	}

	static void IsFocusOff()
	{
		IsFocus = false;
	}

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}
};



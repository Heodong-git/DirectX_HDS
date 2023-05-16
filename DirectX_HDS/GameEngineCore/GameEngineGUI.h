#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <memory>
#include "GameEngineObject.h"
#include <map>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// 불필요한 기능이 있을 수 있지만. 더 귀찮아질수도있으니 그냥 GameEngineObject 상속
class GameEngineGUIWindow : public GameEngineObject, public std::enable_shared_from_this<GameEngineGUIWindow>
{
	friend class GameEngineGUI;

private:
	void Begin()
	{
		std::string_view View = GetName();

		ImGui::Begin(View.data());
	}
	void End()
	{
		ImGui::End();
	}

public:
	virtual void Start() {}
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) = 0;
};

class GameEngineGUI
{
public:
	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

	static void Initialize();
	// 현재 레벨, 델타타임을 받는다. 
	static void Render(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime);
	static void Release();

	template <typename WindowType>
	static std::shared_ptr<GameEngineGUIWindow> GUIWindowCreate(const std::string_view& _Name)
	{
		std::string UpperString = GameEngineString::ToUpper(_Name);
		
		// 맵을탐색하여 이런 이름의 데이터가 이미 있다면
		// end가 아니라는 것은 이미 데이터가 있다는 의미. 
		if (AllWindow.end() != AllWindow.find(UpperString))
		{
			MsgAssert("이런 이름을 가진 GUI 윈도우가 이미 존재합니다." + std::string(_Name));
			return nullptr;
		}

		std::shared_ptr<GameEngineGUIWindow> WindowPtr;
		// 템플릿타입 클래스를 생성하고, WindowPtr이 받고, 그걸 map에 저장 ㄷㄷ 
		AllWindow[UpperString] = WindowPtr = std::make_shared<WindowType>();
		WindowPtr->SetName(UpperString);
		WindowPtr->Start();

		// 생성한 window의 포인터를 반환 
		return WindowPtr;
	}

	// gui window를 컨버트타입으로 dynamic cast 하여 반환 
	template <typename ConvertType>
	static std::shared_ptr<ConvertType> FindGUIWindowConvert(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineGUIWindow> Window = FindGUIWindow(_Name);
		
		return std::dynamic_pointer_cast<ConvertType>(Window);
	}

	// 생성한 GUI Window를 이름으로 찾는다. 
	static std::shared_ptr<GameEngineGUIWindow> FindGUIWindow(const std::string_view& _Name)
	{
		// 대문자변환
		std::string UpperString = GameEngineString::ToUpper(_Name);
		
		// 인자가 string_view 이고, map의 key가 string이기 때문에, 변환한 string을 넣어서 find 
		std::map<std::string, std::shared_ptr<GameEngineGUIWindow>>::iterator FindIter = AllWindow.find(UpperString);
		
		// 해당하는 키값의 데이터가 없다면 nullptr 반환
		if (AllWindow.end() == FindIter)
		{
			return nullptr;
		}
		// 데이터를 찾았다면 인자로 들어온 키값에 해당하는 데이터 반환
		return FindIter->second;
	}
protected:

private:
	// GUI를 사용하여 생성하는 윈도우창을 저장할 자료구조 
	static std::map<std::string, std::shared_ptr<GameEngineGUIWindow>> AllWindow;
};

// imgui 버튼생성 인터페이스 , 어. 
// 1. 실행할 클래스멤버함수를 생성
// 2. 코어윈도우를 상속받은 클래스를 만들어서 아래처럼 함수포인터를 넘겨준다. 
// std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
// Window->Test = std::bind(&CTitleLevel::TestFunction, this);
// Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);
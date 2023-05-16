#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <memory>
#include "GameEngineObject.h"
#include <map>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// ���ʿ��� ����� ���� �� ������. �� ������������������ �׳� GameEngineObject ���
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
	// ���� ����, ��ŸŸ���� �޴´�. 
	static void Render(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime);
	static void Release();

	template <typename WindowType>
	static std::shared_ptr<GameEngineGUIWindow> GUIWindowCreate(const std::string_view& _Name)
	{
		std::string UpperString = GameEngineString::ToUpper(_Name);
		
		// ����Ž���Ͽ� �̷� �̸��� �����Ͱ� �̹� �ִٸ�
		// end�� �ƴ϶�� ���� �̹� �����Ͱ� �ִٴ� �ǹ�. 
		if (AllWindow.end() != AllWindow.find(UpperString))
		{
			MsgAssert("�̷� �̸��� ���� GUI �����찡 �̹� �����մϴ�." + std::string(_Name));
			return nullptr;
		}

		std::shared_ptr<GameEngineGUIWindow> WindowPtr;
		// ���ø�Ÿ�� Ŭ������ �����ϰ�, WindowPtr�� �ް�, �װ� map�� ���� ���� 
		AllWindow[UpperString] = WindowPtr = std::make_shared<WindowType>();
		WindowPtr->SetName(UpperString);
		WindowPtr->Start();

		// ������ window�� �����͸� ��ȯ 
		return WindowPtr;
	}

	// gui window�� ����ƮŸ������ dynamic cast �Ͽ� ��ȯ 
	template <typename ConvertType>
	static std::shared_ptr<ConvertType> FindGUIWindowConvert(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineGUIWindow> Window = FindGUIWindow(_Name);
		
		return std::dynamic_pointer_cast<ConvertType>(Window);
	}

	// ������ GUI Window�� �̸����� ã�´�. 
	static std::shared_ptr<GameEngineGUIWindow> FindGUIWindow(const std::string_view& _Name)
	{
		// �빮�ں�ȯ
		std::string UpperString = GameEngineString::ToUpper(_Name);
		
		// ���ڰ� string_view �̰�, map�� key�� string�̱� ������, ��ȯ�� string�� �־ find 
		std::map<std::string, std::shared_ptr<GameEngineGUIWindow>>::iterator FindIter = AllWindow.find(UpperString);
		
		// �ش��ϴ� Ű���� �����Ͱ� ���ٸ� nullptr ��ȯ
		if (AllWindow.end() == FindIter)
		{
			return nullptr;
		}
		// �����͸� ã�Ҵٸ� ���ڷ� ���� Ű���� �ش��ϴ� ������ ��ȯ
		return FindIter->second;
	}
protected:

private:
	// GUI�� ����Ͽ� �����ϴ� ������â�� ������ �ڷᱸ�� 
	static std::map<std::string, std::shared_ptr<GameEngineGUIWindow>> AllWindow;
};

// imgui ��ư���� �������̽� , ��. 
// 1. ������ Ŭ��������Լ��� ����
// 2. �ھ������츦 ��ӹ��� Ŭ������ ���� �Ʒ�ó�� �Լ������͸� �Ѱ��ش�. 
// std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
// Window->Test = std::bind(&CTitleLevel::TestFunction, this);
// Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);
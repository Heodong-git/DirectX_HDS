#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>

#include <GameEngineBase\GameEngineString.h>

#include "GameEngineLevel.h"

// ���� :
class GameEngineCore
{
public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// �ھ����� functional �� Ȱ���Ͽ� ����, ����� ������ �Լ��� �޴´�.
	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End);

	template<typename LevelType>
	static void CreateLevel(const std::string_view& _Name = "") 
	{
		// ���⼭ shared ptr�� ��ü�� ������ ���� �ʳ�?? 
		// �ƴѰ�? 
		// ��¶�� ��ü����
		LevelType* NewLevel = new LevelType();

		// �̸��� ������ string ����
		std::string Name;

		// ���� ���ڷ� ���� �̸��� �����ٸ�. assert 
		if (_Name == "")
		{

		}

		// ���ڷ� ���� ���ڿ��� �빮�ڷ� ��ȯ�Ͽ� ����
		Name = GameEngineString::ToUpper(Name);
		// �ʿ� �߰�
		LevelMap.insert(Name, NewLevel);
	}
	static void ChangeLevel(const std::string_view& _Name);

protected:

private:
	static void EngineStart();
	static void EngineUpdate();
	static void EngineEnd();

	// ���ڿ� Ű������ ������ �����ϴ� ��
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
};


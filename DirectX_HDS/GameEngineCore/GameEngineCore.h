#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>

#include <GameEngineBase\GameEngineString.h>

#include "GameEngineLevel.h"

// Ό³Έν :
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

	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End);

	template<typename LevelType>
	static void CreateLevel(const std::string_view& _Name = "") 
	{
		LevelType* NewLevel = new LevelType();

		std::string Name;

		if (_Name == "")
		{

		}

		Name = GameEngineString::ToUpper(Name);
		LevelMap.insert(Name, NewLevel);
	}
	static void ChangeLevel(const std::string_view& _Name);

protected:

private:
	static void EngineStart();
	static void EngineUpdate();
	static void EngineEnd();

	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
};


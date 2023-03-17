#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>

#include <GameEngineBase\GameEngineString.h>

#include "GameEngineLevel.h"

// 설명 :
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

	// 코어실행시 functional 을 활용하여 시작, 종료시 실행할 함수를 받는다.
	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End);

	template<typename LevelType>
	static void CreateLevel(const std::string_view& _Name = "") 
	{
		// 여기서 shared ptr로 객체를 만들어야 하지 않나?? 
		// 아닌가? 
		// 어쨋든 객체생성
		LevelType* NewLevel = new LevelType();

		// 이름을 저장할 string 선언
		std::string Name;

		// 만약 인자로 들어온 이름이 없었다면. assert 
		if (_Name == "")
		{

		}

		// 인자로 들어온 문자열을 대문자로 변환하여 저장
		Name = GameEngineString::ToUpper(Name);
		// 맵에 추가
		LevelMap.insert(Name, NewLevel);
	}
	static void ChangeLevel(const std::string_view& _Name);

protected:

private:
	static void EngineStart();
	static void EngineUpdate();
	static void EngineEnd();

	// 문자열 키값으로 레벨을 저장하는 맵
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
};


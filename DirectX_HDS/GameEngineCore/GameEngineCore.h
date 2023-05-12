#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <typeinfo>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

#include <GameEngineBase\GameEngineString.h>
#include <GameEngineBase\GameEngineDebug.h>
#include "GameEngineLevel.h"

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
	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos = { 0, 0 }, float4 _Size = { 1280, 720 });

	template<typename LevelType>
	static std::shared_ptr<LevelType> CreateLevel(const std::string_view& _Name = "")
	{
		// shared_ptr 로 레벨 생성
		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();

		// 문자열을 받고.
		std::string Name = _Name.data();

		// 만약 문자열이 비어있다면
		if (_Name == "")
		{
			// rtti 활용, 생성한 레벨의 클래스이름과 동일한 문자열을
			// string 에 담아주고 , 그 이름으로 만들 수 있게 한다.

			const type_info& Info = typeid(LevelType);
			// 클래스이름을 문자열로 저장하고
			Name = Info.name();
			// 문자열 앞쪽에 class 공백을 지워준다.
			Name.replace(0, 6, "");
		}

		// 문자열을 대문자로 변경 (사고방지)
		Name = GameEngineString::ToUpper(Name);

		// 만약 같은 이름으로 이미 레벨이 생성된 경우 예외처리
		if (LevelMap.end() != LevelMap.find(Name))
		{
			MsgAssert("같은 이름의 레벨을 2개 만들수는 없습니다.");
		}

		// 새로 생성한 레벨 초기화(로딩)
		LevelInit(NewLevel);
		// 코어가 소유한 map 에 저장
		LevelMap.insert(std::make_pair(Name, NewLevel));

		// 생성한 레벨을 shared ptr 전용 dynamic cast 로 형변환하여 반환 
		return std::dynamic_pointer_cast<LevelType>(NewLevel);
	}

	static void ChangeLevel(const std::string_view& _Name);

	static std::shared_ptr<GameEngineLevel> GetCurLevel()
	{
		return MainLevel;
	}

protected:

private:
	static void CoreResourcesInit();
	static void CoreResourcesEnd();

	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level);

	static void EngineStart(std::function<void()> __ContentsStart);
	static void EngineUpdate();
	static void EngineEnd(std::function<void()> __ContentsEnd);

	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
	static std::shared_ptr<GameEngineLevel> MainLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
};

